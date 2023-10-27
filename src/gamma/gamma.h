#ifndef GAMMA_H_INCLUDED
#define GAMMA_H_INCLUDED

#include <vector>
#include <unordered_map>
#include <math.h>
#include <cassert>
#include <queue>

#include "../util/utility.h"

using namespace std;

class DAG {
public:
    class Node;
    class Edge;
    class Node {
    public:
        int number;
        string type;
        vector<DAG::Edge*> in_edges;
        vector<DAG::Edge*> out_edges;
        vector<vector<int>> function_bits;
        string get_graphviz_style();
    };
    class Edge {
    public:
        DAG::Node* from;
        DAG::Node* to;
        int from_slot;
        int to_slot;
        Edge(DAG::Node* from, DAG::Node* to, int from_slot, int to_slot);
    };
    vector<DAG::Node*> vertices;
    void add_edge(DAG::Node* from, DAG::Node* to,int from_slot, int to_slot);
    DAG::Node* get_node(int nr);
    DAG* clone_DAG();
    DAG* create_bipartite();
    void remove_double_wire_usages();
    void print_graph(string name = "gamma");
    vector<vector<DAG::Edge*>> color_graph(int colors);
    void color_path(unordered_map<DAG::Edge*, int> &edge_colors, DAG::Edge* e, int alpha, int beta);
    vector<DAG*> split_into_gamma1(int nr_of_graphs = 2);
    DAG(int size);
    DAG();
    vector<uint> get_stats();
    void reduce_fan_out(uint max_outdegree);
    void reduce_fan_out2(uint max_outdegree);
    DAG::Node* create_recursive_slot_tree(vector<DAG::Node*> nodes_to_add,uint max_outdegree);
    void make_copy_gate_tree(unordered_map<DAG::Node*,vector<DAG::Node*>> &all_copy_gates, DAG::Node* v, uint max_outdegree);
    void make_copy_gate_tree2(unordered_map<DAG::Node*,vector<DAG::Node*>> &all_copy_gates, DAG::Node* v, uint max_outdegree);
    vector<DAG::Node*> add_copy_gate_tree(DAG::Node* v, uint l, uint max_outdegree);
    vector<DAG::Node*> add_copy_gate_tree_rec(DAG::Node* v, uint l, uint max_outdegree, uint curr);
    vector<pair<DAG::Node*,DAG::Node*>> transform_fixed_multi_pole_auxiliary_graph();
    pair< DAG*, pair < unordered_map<int, int> ,  pair < unordered_map<int, vector<int> > ,  unordered_map<int, vector<int> > >  > >   transform_in_place_graph(uint max_outdegree = 2);
    
};

DAG* read_SHDL_to_Gamma(string filename);

#endif // GAMMA_H_INCLUDED
