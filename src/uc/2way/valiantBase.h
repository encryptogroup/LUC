#ifndef VALIANTBASE_H
#define VALIANTBASE_H

#include <iostream>
#include <limits.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <queue>
#include <list>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <stdint.h>
#include <unordered_set>

#include "../../gamma/gamma.h"
#include "../../util/utility.h"

using namespace std;


class ValiantBase {
public:
    struct Node;
    struct Edge;
    struct Edge {
        Node* from;
        Node* to;
        int from_slot;
        int to_slot;

        Edge(Node* from, Node* to, int from_slot, int to_slot);
        void print_edge(ofstream& os);
    };
    struct Node {
        uint32_t number;

        string identifier;


        vector <ValiantBase::Edge*> in_edges;
        vector <ValiantBase::Edge*> out_edges;
        ValiantBase::Edge* get_in_edge(int slot);
        ValiantBase::Edge* get_out_edge(int slot);
        Node* get_parent(int slot);
        Node* get_child(int slot);
        void remove_in_edge(int slot);
        void remove_out_edge(int slot);

        /* Bool true if node is a pole and false otherwise */
        bool is_pole;
        /* Bool true if node is a pole of the outest graph and false otherwise */
        bool is_outest_pole;

        // The type of the gate, this can be x, y, copy, input, output or gate
        string type;
        /* Control_bit for X and Y switches, function table for the poles (universal gates) */
        uint16_t control_bit;

        // True if the pole is forwarding its inputs to a k-input gate
        bool is_forwarding;

        // True if the pole has more than two inputs
        bool is_k_input;

        // Number of inputs to this pole / gate, only guaranteed to be defined if pole is k-input gate
        int num_inputs;

        // Vector of the additional inputs coming from forwarding poles
        vector<Node*> additional_inputs;

        int superpole_num;

        int superpole_position;


        Node(uint32_t num, string position, bool is_pole, string type);


        // For printing the circuit into file
        string get_style();
        // Gives information about the position of this node in the EUG
        string position;
    };

    struct Superpole {
        // Number identifying the node
        uint32_t number;

        int pole_number;
        int node_number;
        Node* pole_array[2];
        Node* node_array[3];

        // Defines the routing to be used inside the block
        int input_vector[2];
        int output_vector[2];

        Node* get_input_node();
        Node* get_output_node();
        void  embed_block();


        Superpole(uint32_t num, Node* pole1, Node* pole2, Node* node1, Node* node2, Node* node3);
        string position;
    };

public:
    vector<Node*> poles;
    vector<Node*> nodes;
    // Left subgraph
    struct ValiantBase* sub_left;
    // Right subgraph
    struct ValiantBase* sub_right;
    // Number of nodes
    uint32_t node_number;

    // ValiantBase(uint32_t number, string position, bool side, bool outest);
    ValiantBase();
    virtual void create_skeleton(uint32_t inputs, uint32_t gates, uint32_t outputs, string position, bool outest);
    void create_poles(uint32_t inputs, uint32_t gates, uint32_t outputs, string position, bool outest);
    void create_nodes(uint32_t node_number, string position);
    void generic_node_path(uint32_t i, uint32_t j);
    // With special property
    void add_edge(Node* from, Node* to, int);
    void add_edge(Node* from, Node* to, int from_slot, int to_slot);
    void remove_edge(ValiantBase::Edge* e);
    void print_graph(string f);
    void print_nodes(ofstream& os);
    void print_edges(ofstream& os);
    virtual void remove_x_switches();


    // True if this is the outest graph
    bool is_outest;
    virtual void edge_embed_gamma1(DAG* g);

    vector<Superpole*> superpoles;
    int superpole_number;
};


#endif /* VALIANTBASE_H */
