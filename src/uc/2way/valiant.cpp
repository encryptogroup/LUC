#include "valiant.h"
#include <math.h>
#include <unordered_set>
#include <unordered_map>
#include <cassert>

// Basic Valiant's 2-way split construction
Valiant2Way::Valiant2Way(uint32_t inputs, uint32_t gates, uint32_t outputs, string position, bool outest){
    uint32_t n = inputs + gates + outputs;
    if (n <= 4){
        is_outest = outest;
        sub_left = 0;
        sub_right = 0;
        create_poles(inputs, gates, outputs, position, outest);
        assert(n > 0);
        switch(n){
            case 1:
                cerr << "Recursion called with size 1" << "\n";
                return;
            case 2:
                node_number = 0;
                add_edge(poles[0], poles[1], 1);
                return;
            case 3:
                node_number = 0;
                add_edge(poles[0], poles[1], 1);
                add_edge(poles[1], poles[2], 1);
                return;
            case 4:
                create_nodes(3, position);
                add_edge(poles[0], nodes[0], 1);
                add_edge(nodes[0], poles[1], 1);
                add_edge(nodes[0], nodes[1], 0);
                add_edge(poles[1], nodes[1], 1);
                add_edge(nodes[1], poles[2], 1);
                add_edge(nodes[1], nodes[2], 0);
                add_edge(poles[2], nodes[2], 1);
                add_edge(nodes[2], poles[3], 1);
                nodes[0]->type = "copy";
                nodes[1]->type = "x";
                nodes[2]->type = "y";
                return;
        }
    } else{
        create_skeleton(inputs, gates, outputs, position ,outest);
        // Now create the nodes of the next layer, e.g. create the subgraphs
        Valiant2Way* l = new Valiant2Way(0,superpole_number-1,0, position + "l", false);
        Valiant2Way* r = new Valiant2Way(0,superpole_number-1,0, position + "r", false);
        // Now connect the graph with its subgraph
        sub_left = l;
        sub_right = r;
        for(int i=0; i < superpole_number-1;i++){
            // Connect nodes to the subgraph poles       
            Superpole* curr = superpoles[i];
            add_edge(curr->get_output_node(),sub_left->poles[i], 1, 0);
            add_edge(curr->get_output_node(),sub_right->poles[i], 0, 0);
            
            // Connect subgraph poles to nodes
            curr = superpoles[i+1];
            add_edge(sub_left->poles[i], curr->get_input_node(),0, 1);
            add_edge(sub_right->poles[i], curr->get_input_node(),0, 0);
        }   
    } 
}
