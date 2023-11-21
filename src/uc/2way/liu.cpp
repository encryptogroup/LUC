#include "liu.h"
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <math.h>

// Creates the weak Liu 2-Way construction
WeakLiu2Way::WeakLiu2Way(uint32_t inputs, uint32_t gates, uint32_t outputs, string position, bool outest) {
    uint32_t n = inputs + gates + outputs;
    assert(n > 1);
    if (n == 2) {
        is_outest = outest;
        sub_left = 0;
        sub_right = 0;
        create_poles(inputs, gates, outputs, position, outest);
        nodes.push_back(new Node(1, position, false, "x"));
        add_edge(poles[0], nodes[0], 1, 1);
        add_edge(nodes[0], poles[1], 1, 1);
        return;
    }
    else {
        create_skeleton(inputs, gates, outputs, position, outest);
        assert(superpole_number >= 1);

        // Create the subgraphs
        WeakLiu2Way* l = new WeakLiu2Way(0, superpole_number, 0, position + "l", false);
        WeakLiu2Way* r = new WeakLiu2Way(0, superpole_number, 0, position + "r", false);

        // Connect the subgraphs
        sub_left = l;
        sub_right = r;
        int i = 0;
        for (Superpole* sp : superpoles) {
            // Connect from subgraphs to current graph
            if (i != 0) {
                add_edge(sub_left->poles[sp->number - 1], sp->get_input_node(), 0, 1);
                add_edge(sub_right->poles[sp->number - 1], sp->get_input_node(), 0, 0);
            }

            // Connect from current graph to subgraph
            if (i != superpole_number - 1) {
                add_edge(sp->get_output_node(), sub_left->poles[sp->number - 1], 1, 0);
                add_edge(sp->get_output_node(), sub_right->poles[sp->number - 1], 0, 0);
            }
            i++;
        }
    }
}

// Creates the Liu 2-Way construction
Liu2Way::Liu2Way(uint32_t inputs, uint32_t gates, uint32_t outputs, string position, bool outest) {
    uint32_t n = inputs + gates + outputs;
    assert(n > 1);
    if (n == 2) {
        is_outest = outest;
        sub_left = 0;
        sub_right = 0;
        create_poles(inputs, gates, outputs, position, outest);
        nodes.push_back(new Node(1, position, false, "x"));
        add_edge(poles[0], nodes[0], 1, 1);
        add_edge(nodes[0], poles[1], 1, 1);
        return;
    }
    else {
        create_skeleton(inputs, gates, outputs, position, outest);
        assert(superpole_number >= 1);

        // Create the subgraphs
        Liu2Way* l = new Liu2Way(0, superpole_number, 0, position + "l", false);
        Liu2Way* r = new Liu2Way(0, superpole_number, 0, position + "r", false);

        // Connect the subgraphs
        sub_left = l;
        sub_right = r;
        int i = 0;
        for (Superpole* sp : superpoles) {
            // Connect from subgraphs to current graph
            Liu2Way::Node* pole_left = sub_left->poles[sp->number - 1];
            Liu2Way::Node* pole_right = sub_right->poles[sp->number - 1];
            if (i != 0) {
                Liu2Way::Node* predecessor_left = pole_left->get_parent(1);
                Liu2Way::Node* predecessor_right = pole_right->get_parent(1);
                pole_left->remove_in_edge(1);
                pole_right->remove_in_edge(1);
                add_edge(predecessor_left, sp->get_input_node(), 1, 1);
                add_edge(predecessor_right, sp->get_input_node(), 1, 0);
            }

            // Connect from current graph to subgraph
            if (i != superpole_number - 1) {
                Liu2Way::Node* successor_left = pole_left->get_child(1);
                Liu2Way::Node* successor_right = pole_right->get_child(1);
                pole_left->remove_out_edge(1);
                pole_right->remove_out_edge(1);
                add_edge(sp->get_output_node(), successor_left, 1, 1);
                add_edge(sp->get_output_node(), successor_right, 0, 1);
            }
            i++;
        }
    }
}



// Edge-embedding algorithm for Liu's 2-Way construction and Gamma_1 graphs
void Liu2Way::edge_embed_gamma1(DAG* g) {
    assert(poles.size() == g->vertices.size());
    if (poles.size() <= 2) {
        // do recursion base
        if (!g->vertices[0]->out_edges.empty()) {
            nodes[0]->control_bit = 0;
        }
        return;
    }
    // This will be the graph that contains the information which edges should be embedded in the next recursion step
    DAG* g2 = new DAG(superpole_number);

    unordered_map<string, vector<vector<int>>> position_mapping;

    for (DAG::Node* u_g : g->vertices) {
        Liu2Way::Node* u = poles[u_g->number - 1];
        Superpole* block_u = superpoles[u->superpole_num - 1];
        if (!u_g->out_edges.empty()) {
            Liu2Way::Node* v = poles[u_g->out_edges[0]->to->number - 1];
            Superpole* block_v = superpoles[v->superpole_num - 1];

            // If u and v are in the same block, just route u to v inside block
            if (block_u == block_v) {
                block_u->output_vector[u->superpole_position - 1] = v->superpole_position;
            }
            else {
                // add (block_u,block_v) to supergraph to embed it later
                g2->add_edge(g2->vertices[block_u->number - 1], g2->vertices[block_v->number - 1],0,0);
                string edge = to_string(block_u->number) + "->" + to_string(block_v->number);
                vector<int> position_information = { u->superpole_position,v->superpole_position };
                position_mapping[edge].push_back(position_information);
            }
        }
    }

    // Divide the supergraph in two gamma1 graphs by 2 coloring
    vector<DAG*> dag1s = g2->split_into_gamma1();
    assert(dag1s.size() == 2);
    vector<bool> sides = { true, false };
    for (bool side : sides) {
        DAG* sg = (side) ? dag1s[0] : dag1s[1];
        int side_num = (side) ? 0 : 1;
        for (DAG::Node* u : sg->vertices) {
            if (!u->out_edges.empty()) {
                DAG::Node* v = u->out_edges[0]->to;
                Superpole* block_u = superpoles[u->number - 1];
                Superpole* block_v = superpoles[v->number - 1];
                Liu2Way::Node* block_u_out_rec = block_u->get_output_node()->get_child(side);
                Liu2Way::Node* block_v_in_rec = block_v->get_input_node()->get_parent(side);
                block_u_out_rec->control_bit = 1;
                block_v_in_rec->control_bit = 1;
                string edge = to_string(block_u->number) + "->" + to_string(block_v->number);
                vector<vector<int>> superpole_position_vector = position_mapping[edge];
                int u_superpole_pos = superpole_position_vector[superpole_position_vector.size() - 1][0];
                int v_superpole_pos = superpole_position_vector[superpole_position_vector.size() - 1][1];
                position_mapping[edge].pop_back();
                block_u->output_vector[u_superpole_pos - 1] = 3 + side_num;
                block_v->input_vector[side_num] = v_superpole_pos;
            }
        }
    }

    // Now call block edge embedding for all blocks
    for (Superpole* sp : superpoles) {
        sp->embed_block();
    }


    // Now do recursion
    if (sub_left) {
        sub_left->edge_embed_gamma1(dag1s[0]);
    }
    if (sub_right) {
        sub_right->edge_embed_gamma1(dag1s[1]);
    }
}

// Removes unnecessary x switches, i.e., they have only one input. This can happen by short cutting the recursion points in Liu's EUG construction.
void Liu2Way::remove_x_switches() {
    for (Liu2Way::Node* node : nodes) {
        if (node->type == "x" && node->in_edges.size() == 1) {
            // We have an unnecessary x switch
            ValiantBase::Edge* e_in = node->in_edges[0];
            ValiantBase::Edge* e_out = node->out_edges[0];
            remove_edge(e_in);
            remove_edge(e_out);
            add_edge(e_in->from, e_out->to, e_in->from_slot, e_out->to_slot);
            ValiantBase::Node* child = e_out->to;
            if (child->type == "y") {
				// Why check type x here?
                if ((child->get_parent(true) == child->get_parent(0)) && (child->get_parent(1)->type == "x")) {
                    // Merge them to one node (by removing parent node)
                    ValiantBase::Node* parent = e_in->from;
                    ValiantBase::Edge* parent_left_in_edge = parent->get_in_edge(1);
                    ValiantBase::Edge* parent_right_in_edge = parent->get_in_edge(0);
                    // remove old out edges of parents of parent
                    remove_edge(parent_left_in_edge);
                    remove_edge(parent_right_in_edge);
                    // remove old in edges of child
                    remove_edge(child->in_edges[0]);
                    remove_edge(child->in_edges[1]);
                    // add the edges skipping parent
                    add_edge(parent_left_in_edge->from, child, parent_left_in_edge->from_slot, 1);
                    add_edge(parent_right_in_edge->from, child, parent_right_in_edge->from_slot, 0);
                    // set control bit correctly (if parents swapped wires, we have to swap too)
                    if (parent->control_bit == 1) {
                        child->control_bit = 1 - child->control_bit;
                    }
                }
            }
        }
    }
    if (sub_left) {
        sub_left->remove_x_switches();
    }
    if (sub_right) {
        sub_right->remove_x_switches();
    }
}
