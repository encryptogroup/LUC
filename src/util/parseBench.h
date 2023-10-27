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
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <random>
#include <chrono>

#include "utility.h"
using namespace std;

class Graph{
    public:
        class Node{
            public:
                Node(int number, string name, string type);
                int number;
                string name;
                string type;
                vector<int> function_bits;
                vector<Node*> inputs;
                vector<Node*> outputs;
                vector<Graph::Node*> copy_gates;
        };
        
        vector<Node*> nodes;
};

void parse_bench(string str_filename);
void make_copy_gate_tree(Graph::Node* v);
void write_shdl_line(ofstream &os, Graph::Node* v);
void write_node_with_copy_gates(ofstream &os, Graph::Node* u, int &number);
void parse_bench(string str_filename, int copies);
Graph* create_random_graph(uint num_inputs, uint num_gates, uint num_outputs, uint max_outdegree, uint max_indegree, string filename);
Graph* convert_into_fanout2(Graph* g);
void shdl_to_bench(string filename);
