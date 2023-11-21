#include "valiantBase.h"
#include <math.h>
#include <unordered_set>
#include <unordered_map>
#include <cassert>

// Constructor for the superpoles
ValiantBase::Superpole::Superpole( uint32_t num, Node* pole1, Node* pole2, Node* input_node, Node* middle_node, Node* output_node){
    number = num;

    // Set poles
    pole1->superpole_num = num;
    pole1->superpole_position = 1;
    pole_array[0] = pole1;
    pole_number = 1;

    if (pole2){
        pole2->superpole_num = num;
        pole2->superpole_position = 2;
        pole_array[1] = pole2;
        pole_number = 2;
    }
    

    // Set nodes
    node_number = 0;
    Node* nodes [3] = {input_node, middle_node, output_node};
    for (int i=0; i<3;i++){
        Node* curr = nodes[i];
        if (curr){
            curr->superpole_num = num;
            curr->superpole_position = i+1;
            node_array[i] = curr;
            node_array[i]->type = "x";
            node_number++;
        }else{
            node_array[i] = 0;
        }
    }
    if (!input_node){
        node_array[1]->type = "copy";
    }
    if (!middle_node){
        node_array[0]->type = "y";
    } else if (!output_node){
        node_array[1]->type = "y";
    }

    // Set default input and output vectors
    input_vector[0] = 0;
    input_vector[1] = 0;
    output_vector[0] = 0;
    output_vector[1] = 0;
    
}

ValiantBase::Node* ValiantBase::Superpole::get_input_node(){
    return node_array[0];
}

ValiantBase::Node* ValiantBase::Superpole::get_output_node(){
    return node_array[2];
}

string ValiantBase::Node::get_style(){
    if (type == "x"){
        if (control_bit == 0){
            return "[ style=filled,fillcolor=\"red\" ]";
        } else if (control_bit == 1){
            return "[ style=filled,fillcolor=\"magenta\" ]";
        } else{
            return "[ style=filled,fillcolor=\"white\" ]";
        }
    } else if (type == "y"){
        if (control_bit == 0){
            return "[ style=filled,fillcolor=\"blue\" ]";
        } else if (control_bit == 1){
            return "[ style=filled,fillcolor=\"cyan\" ]";
        } else{
            return "[ style=filled,fillcolor=\"white\" ]";
        }
    } else if (type == "copy"){
        return "[ style=filled,fillcolor=\"gray33\" ]";
    } else if (type == "gate"){
        return "[ style=filled,fillcolor=\"yellow\" ]";
    } else if (type == "input"){
        return "[ style=filled,fillcolor=\"green\" ]";
    } else if (type == "output"){
        return "[ style=filled,fillcolor=\"darkgreen\" ]";
    } else{ 
        return "[ style=filled,fillcolor=\"gray\" ]";
    }
}

// Edge-embeds a block / Superpole, i.e., sets the programming bits of this block
void ValiantBase::Superpole::embed_block(){
    if (input_vector[0] == 1){
        node_array[0]->control_bit = 0;
    }
    if (input_vector[0] == 2){
        node_array[0]->control_bit = 1;
        node_array[1]->control_bit = 1;
    }

    if (input_vector[1] == 1){
        node_array[0]->control_bit = 1;
    }
    if (input_vector[1] == 2){
        node_array[0]->control_bit = 0;
        node_array[1]->control_bit = 1;
    }

    if(output_vector[0] == 2){
        node_array[1]->control_bit = 0;
    }

    if(output_vector[0] == 3){
        node_array[1]->control_bit = 1;
        node_array[2]->control_bit = 1;
    }

    if(output_vector[0] == 4){
        node_array[1]->control_bit = 1;
        node_array[2]->control_bit = 0;
    }

    if (output_vector[1] == 3){
        node_array[2]->control_bit = 0;
    }

    if (output_vector[1] == 4){
        node_array[2]->control_bit = 1;
    }
}


// prints all nodes of the Valiant DAG
void ValiantBase::print_nodes(ofstream &os){
    vector<ValiantBase::Node*> all_nodes[] = {nodes, poles};
    unsigned long sizes [] = {nodes.size(), poles.size()};
    string styles [] = {"[ style=filled,fillcolor=\"gray\" ]", "[ style=filled,fillcolor=\"gray33\" ]"};
    string forward_style = "[ style=filled,fillcolor=\"darkgoldenrod4\" ]";
    string k_input_style = "[ style=filled,fillcolor=\"gold\" ]";
    string outest_pole_style = "[ style=filled,fillcolor=\"yellow\" ]";
    styles[1] = (is_outest) ? "[ style=filled,fillcolor=\"yellow\" ]" : styles[1];
    //int i = (is_outest) ? 0 : 1;
    int i = 0;
    for (;i<2;i++){
        vector<ValiantBase::Node*> curr = all_nodes[i];
        unsigned long size = sizes[i];
        for (uint32_t j=0; j<size;j++){
            string style = styles[i];
            if (curr[j]->is_forwarding){
                style = forward_style;
            } else if (curr[j]->is_k_input){
                style = k_input_style;
            }
            os << "node " << style << " " << curr[j]->identifier << ";\n";
        }
    }
    ValiantBase* sub_graphs[] = {sub_left, sub_right};
    for (int i=0; i<2;i++){
        if (sub_graphs[i]){
            sub_graphs[i]->print_nodes(os);
        }
    }
}

// prints all edges of the Valiant DAG
void::ValiantBase::print_edges(ofstream &os){
    vector<ValiantBase::Node*> all_nodes [] = {nodes, poles};
    int i = 0;
    for (; i<2;i++){
        vector<ValiantBase::Node*> curr_set = all_nodes[i];
        for(ValiantBase::Node* curr: curr_set){
            for (ValiantBase::Edge* e_out: curr->out_edges){
                e_out->print_edge(os);

            }
        }
    }
    ValiantBase* sub_graphs[] = {sub_left, sub_right};
    for (int i=0; i<2;i++){
        if (sub_graphs[i]){
            sub_graphs[i]->print_edges(os);
        }
    }
}

// Prints the complete Valiant graph
void ValiantBase::print_graph(string f){
    string filename = "graphviz/"+f;
    ofstream os;
    os.open(filename);
    os << "digraph{\n";
    // We need two passes over the graph since the nodes must be defined before the corresponding edges for graphviz
    print_nodes(os);
    print_edges(os);
    os << "}";
    os.close();
}

void ValiantBase::Edge::print_edge(ofstream &os){
    string slot = "";
    if (from_slot == 1){
        slot += "l";
    } else{
        slot += "r";
    }
    if (to_slot == 1){
        slot += "l";
    } else{
        slot += "r";
    }
    string slot_label = " [ label = \"" + slot + "\" ] ";
    os << "\"" << from->identifier << "\"" << " -> " << "\"" << to->identifier << "\"" << slot_label << "\n";
}

void ValiantBase::create_nodes(uint32_t node_number, string position){
    for(uint32_t i = 0; i < node_number; ++i){
        nodes.push_back(new Node(i + 1, position, false, "undefined"));
	}
}


// default constructor
ValiantBase::ValiantBase(){}

// Basic Valiants 2-way split construction
void ValiantBase::create_skeleton(uint32_t inputs, uint32_t gates, uint32_t outputs, string position, bool outest){
    uint32_t n = inputs + gates + outputs;
    if (n <= 0){
        return;
    }
    is_outest = outest;
    sub_left = 0;
    sub_right = 0;

    create_poles(inputs, gates, outputs, position, outest);

    superpole_number = ceil((double (n)/2));
   
    if (n % 2 == 1){
        // Then last block has one pole and node less
        node_number = 3 + 3*(superpole_number - 2);
    } else{
        node_number = 4 + 3*(superpole_number - 2);
    }
    create_nodes(node_number, position);



    // First block
    add_edge(poles[0], nodes[0], 1);
    add_edge(nodes[0], poles[1], 1);
    add_edge(nodes[0], nodes[1], 0);
    add_edge(poles[1], nodes[1], 1);
    superpoles.push_back(new Superpole(1, poles[0], poles[1], 0, nodes[0], nodes[1]));
    

    // Blocks in between
    uint32_t i = 3;
    for(uint32_t j = 3; j < n - 1; j+= 2){
        superpoles.push_back(new Superpole((j-1)/2 + 1, poles[j-1], poles[j], nodes[i-1], nodes[i], nodes[i+1]));
        this->generic_node_path(i, j);
        i += 3;
    }

    // End block
    if(n % 2 == 1){
        // Then we have now only one pole left and need only one node
        superpoles.push_back(new Superpole(superpole_number, poles[poles.size()-1], 0, nodes[node_number-1], 0, 0));
        add_edge(nodes[node_number-1], poles[n-1],true);
    }else{
        // We have an end block with two poles and two nodes
        superpoles.push_back(new Superpole(superpole_number, poles[n-2], poles[n-1], nodes[node_number-2], nodes[node_number-1], 0));
        add_edge(nodes[node_number-2], poles[n-2], 1);
        add_edge(poles[n-2], nodes[node_number-1], 1);
        add_edge(nodes[node_number-2], nodes[node_number-1], 0);
        add_edge(nodes[node_number-1], poles[n-1], 1);
    }
}


// Creates the desired number of poles
void ValiantBase::create_poles(uint32_t inputs, uint32_t gates, uint32_t outputs, string position, bool outest){
    uint32_t pole_num = inputs + gates + outputs;
    for(uint32_t i = 0; i < pole_num; ++i){
        string pos = (outest) ? "" : position;
        string type;
        if (outest){
            if (i < inputs){
                type = "input";
            } else if (i < inputs + gates){
                type = "gate";
            } else{
                type = "output";
            }
        } else{
            if (i == 0){
                type = "copy";
            } else if (i == pole_num - 1){
                type = "y";
            } else{
                type = "x";
            }
        }
        poles.push_back(new Node(i + 1, pos, true, type));
		// For outest poles store that they are outest, i.e., inputs, outputs or gates
		if(outest){
            poles[i]->is_outest_pole = true;
		}
	}
}

// Adds the wiring inside a block
void ValiantBase::generic_node_path(uint32_t i, uint32_t j){
    add_edge(nodes[i - 1], poles[j - 1], 1);
    add_edge(poles[j - 1], nodes[i], 1);
    add_edge(nodes[i - 1], nodes[i], 0);
    add_edge(nodes[i], poles[j], 1);
    add_edge(nodes[i], nodes[i + 1], 0);
    add_edge(poles[j], nodes[i + 1], 1);
}


void ValiantBase::add_edge(Node* from, Node* to, int slot){
    add_edge(from,to,slot,slot);

}

void ValiantBase::add_edge(ValiantBase::Node* from, ValiantBase::Node* to, int from_slot, int to_slot){
    ValiantBase::Edge* e = new ValiantBase::Edge(from, to, from_slot, to_slot);
    to->in_edges.push_back(e);
    from->out_edges.push_back(e);
}

ValiantBase::Edge* ValiantBase::Node::get_in_edge(int slot){
    ValiantBase::Edge* result = 0;
    bool flag = false;
    for(ValiantBase::Edge* e_in: in_edges){
        if ((slot == e_in->to_slot)){
            if (flag){
                cerr << "There is more than one incoming edge per slot" << endl;
            }
            flag = true;
            result = e_in;
        }
    }
    return result;
}

ValiantBase::Edge* ValiantBase::Node::get_out_edge(int slot){
    ValiantBase::Edge* result = 0;
    bool flag = false;
    for(ValiantBase::Edge* e_out: out_edges){
        if ((slot == e_out->from_slot)){
            if (flag){
                cerr << "There is more than one outgoing edge per slot" << endl;
            }
            flag = true;
            result = e_out;
        }
    }
    return result;
}

ValiantBase::Node* ValiantBase::Node::get_parent(int slot){
    ValiantBase::Edge* e_in = get_in_edge(slot);
    if (e_in){
        return e_in->from;
    } else{
        return 0;
    }
}

ValiantBase::Node* ValiantBase::Node::get_child(int slot){
    ValiantBase::Edge* e_out = get_out_edge(slot);
    if (e_out){
        return e_out->to;
    } else{
        return 0;
    }
}

void ValiantBase::Node::remove_in_edge(int slot){
    int removed = 0;
    for(uint i=0; i< in_edges.size(); i++){
        ValiantBase::Edge* e_in = in_edges[i];
        if (e_in->to_slot == slot){
            in_edges.erase(in_edges.begin() + i);
            // Also remove out edge of other side
            int index = find_index<ValiantBase::Edge*>(e_in->from->out_edges,e_in);
            e_in->from->out_edges.erase(e_in->from->out_edges.begin() + index); 
            removed++;
        }
    }
    assert(removed == 1);
}


void ValiantBase::Node::remove_out_edge(int slot){
    int removed = 0;
    for(uint i=0; i< out_edges.size(); i++){
        ValiantBase::Edge* e_out = out_edges[i];
        if (e_out->from_slot == slot){
            out_edges.erase(out_edges.begin() + i);
            // Also remove in edge of other side
            int index = find_index<ValiantBase::Edge*>(e_out->to->in_edges,e_out);
            e_out->to->in_edges.erase(e_out->to->in_edges.begin() + index);
            removed++;
        }
    }
    assert(removed == 1);
}

void ValiantBase::remove_edge(ValiantBase::Edge* e){
    for(uint i=0; i< e->from->out_edges.size(); i++){
        ValiantBase::Edge* e_out = e->from->out_edges[i];
        if (e_out == e){
            e->from->out_edges.erase(e->from->out_edges.begin()+i);
        }
    }
    for(uint i=0; i< e->to->in_edges.size(); i++){
        ValiantBase::Edge* e_in = e->to->in_edges[i];
        if (e_in == e){
            e->to->in_edges.erase(e->to->in_edges.begin()+i);
        }
    }
}

//This function is only used with Liu. This is the default function
void ValiantBase::remove_x_switches(){}


ValiantBase::Node::Node(uint32_t num, string pos, bool pole, string type){
      this->number = num;
      this->is_pole = pole;
      this->is_outest_pole = false;
      this->control_bit = 2;
      this->position = pos;
      this->is_forwarding = false;
      this->is_k_input = false;
      this->superpole_num = -1;
      this->superpole_position = -1;
      this->type = type;
      string tmp = (is_pole) ? "p" : "n";
      this->identifier = tmp + position + "_" + to_string(number);
  }

ValiantBase::Edge::Edge(ValiantBase::Node* from, ValiantBase::Node* to, int from_slot, int to_slot){
    this->from = from;
    this->to = to;
    this->from_slot = from_slot;
    this->to_slot = to_slot;
}

// Edge-embedding algorithm that sets the programming bits of the EUG such that the topology of the graph is the same as in g
// The gate functionality is set later
void ValiantBase::edge_embed_gamma1(DAG* g) {
    if (g->vertices.size() <= 4) {
        if (g->vertices.size() == 3) {
            if (!g->vertices[0]->out_edges.empty() && g->vertices[0]->out_edges[0]->to == g->vertices[2]) {
                // Middle pole must be set in this case
                poles[1]->control_bit = 0;
            }
        }
        if (g->vertices.size() == 4) {
            if (!g->vertices[0]->out_edges.empty() && g->vertices[0]->out_edges[0]->to == g->vertices[1]) {
                // do nothing
            }
            if (!g->vertices[0]->out_edges.empty() && g->vertices[0]->out_edges[0]->to == g->vertices[2]) {
                nodes[1]->control_bit = 1;
            }
            if (!g->vertices[0]->out_edges.empty() && g->vertices[0]->out_edges[0]->to == g->vertices[3]) {
                nodes[1]->control_bit = 0;
                nodes[2]->control_bit = 1;
            }
            if (!g->vertices[1]->out_edges.empty() && g->vertices[1]->out_edges[0]->to == g->vertices[2]) {
                nodes[1]->control_bit = 0;
            }
            if (!g->vertices[1]->out_edges.empty() && g->vertices[1]->out_edges[0]->to == g->vertices[3]) {
                nodes[1]->control_bit = 1;
                nodes[2]->control_bit = 1;
            }
            if (!g->vertices[2]->out_edges.empty() && g->vertices[2]->out_edges[0]->to == g->vertices[3]) {
                nodes[2]->control_bit = 0;
            }
        }
        return;
    }


    // This will be the graph that contains the information which edges should be embedded in the next recursion step
    DAG* g2 = new DAG(superpole_number - 1);

    unordered_map<string, vector<vector<int>>> position_mapping;
    // Iterate over all nodes to iterate through all edges
    for (uint i = 0;i < g->vertices.size();i++) {
        if (g->vertices[i]->out_edges.empty()) {
            // Skip if child not existent
            continue;
        }

        // Setting up variables

        // Get the blocks in which the nodes are in
        // We implicitly assume that node i in g corresponds to pole i in the eug
        ValiantBase::Node* curr = poles[i];
        ValiantBase::Node* child = poles[g->vertices[i]->out_edges[0]->to->number - 1];
        
	int from_slot = g->vertices[i]->out_edges[0]->from_slot;
	int to_slot = g->vertices[i]->out_edges[0]->to_slot;

        int curr_block_num = curr->superpole_num;
        int child_block_num = child->superpole_num;
        ValiantBase::Superpole* curr_block = superpoles[curr_block_num - 1];
        

        //Start Embedding


        if (curr_block_num == child_block_num) {
            // Then we can route inside the supernode
            curr_block->output_vector[curr->superpole_position - 1] = child->superpole_position;
        }
        else {
            // Different blocks, so add edge to g2 to embed it later after 2 coloring
            g2->add_edge(g2->vertices[curr_block_num - 1], g2->vertices[child_block_num - 2], from_slot, to_slot);
            string edge = to_string(curr_block_num) + "->" + to_string(child_block_num);
            vector<int> position_information = { curr->superpole_position,child->superpole_position };
            position_mapping[edge].push_back(position_information);
        }
    }

    // Now iterate over the new graphs
    vector<DAG*> dag1s = g2->split_into_gamma1();
    assert(dag1s.size() == 2);
    int side_num = 0;
    dag1s[0]->print_graph("Embedding1");
    dag1s[1]->print_graph("Embedding2");
    for (DAG* sg : dag1s) {
        for (uint i = 0; i < sg->vertices.size();i++) {
            DAG::Node* curr = sg->vertices[i];
            if (!curr->out_edges.empty()) {
                DAG::Node* child = curr->out_edges[0]->to;
                
                int from_slot = curr->out_edges[0]->from_slot;
                int to_slot = curr->out_edges[0]->to_slot;
                
                ValiantBase::Superpole* curr_block = superpoles[i];
                ValiantBase::Superpole* child_block = superpoles[child->number]; // we need to choose the block with the child number and not child number -1 since the target is always reduced by 1
                // Get the recursion points depending on which side the graph should be embedded
                ValiantBase::Node* curr_block_out_rec;
                ValiantBase::Node* child_block_in_rec;
                if (side_num == 0) {
                    curr_block_out_rec = curr_block->get_output_node()->get_child(1);
                    child_block_in_rec = child_block->get_input_node()->get_parent(1);
                }
                else {
                    curr_block_out_rec = curr_block->get_output_node()->get_child(0);
                    child_block_in_rec = child_block->get_input_node()->get_parent(0);
                }
                int control_bit;
                curr_block_out_rec->control_bit = 1;
                if (child_block->number == curr_block->number + 1) {
                    // Then output recursion point is input recursion point, i.e. curr_block_out_rec = child_block_in_rec
                    // So the former assignment child_block_in_rec->control_num = 1 will be overwritten
                    // Inner path stays inside
                    control_bit = 0;
                }
                else {
                    // We need to go to the next level eug, e.g. we must change from inside to outside
                    control_bit = 1;
                }
                string edge = to_string(curr->number) + "->" + to_string(child->number + 1);
                vector<vector<int>> superpole_position_vector = position_mapping[edge];
                int curr_superpole_pos = superpole_position_vector[superpole_position_vector.size() - 1][0];
                int child_superpole_pos = superpole_position_vector[superpole_position_vector.size() - 1][1];
                position_mapping[edge].pop_back();

                child_block_in_rec->control_bit = control_bit;

                curr_block->output_vector[curr_superpole_pos - 1] = 3 + side_num; // Output vector has possible values 0,1,2,3,4 with 0 being default value for nothing
                if (child_block->input_vector[side_num] != 0) {
                    cout << "Same recursion point used to embed" << endl;
                }
                child_block->input_vector[side_num] = child_superpole_pos;
            }
        }
        side_num++;
    }

    // BLOCK EMBEDDING
    for (ValiantBase::Superpole* block : superpoles) {
        block->embed_block();
    }

    // Recurse over the rest   
    sub_left->edge_embed_gamma1(dag1s[0]);
    sub_right->edge_embed_gamma1(dag1s[1]);
}
