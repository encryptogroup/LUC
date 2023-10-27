
#include "parseBench.h"

#include <cassert>
#include <math.h>
#include <unordered_set>
#include <random>
#include <chrono>
#include <iostream>
#include <fstream>


Graph::Node::Node(int number, string name, string type) {
    this->name = name;
    this->type = type;
    this->number = number;
}

// Parses the given graph in Bench format into the Graph class
Graph* benchToGraph(string str_filename) {
    ifstream is;
    is.open(str_filename);

    string line;
    vector<string> tokens;

    // Create a graph representation
    Graph* g = new Graph();
    int number = 0;
    unordered_map<string, Graph::Node*> map;
    unordered_set<string> circuit_outputs;

    while (getline(is, line)) {
        if (line == "") {
            continue;
        }
        if (line.rfind("INPUT", 0) == 0) {
            int last_pos = line.find_last_of(")");
            string name = line.substr(6, last_pos - 6);
            if (map.find(name) == map.end()) {
                map[name] = new Graph::Node(number, name, "input");
                g->nodes.push_back(map[name]);
                number++;
            }
        }
        else if (line.rfind("OUTPUT", 0) == 0) {
            int last_pos = line.find_last_of(")");
            string name = line.substr(7, last_pos - 7);
            circuit_outputs.insert(name);
        }
        else {
            tokenize(line, tokens);
            if (tokens[0] == "#") {
                continue;
            }
            if (map.find(tokens[0]) == map.end()) {
                string name = tokens[0];
                string type = "gate";
                if (circuit_outputs.find(name) != circuit_outputs.end()) {
                    type = "output";
                }
                Graph::Node* curr_node = new Graph::Node(number, name, type);
                map[name] = curr_node;
                g->nodes.push_back(curr_node);
                number++;
                vector<Graph::Node*> inputs;
                int i = 5;
                while (tokens[i] != ")") {
                    if (tokens[i].substr(tokens[i].size() - 1, tokens[i].size() - 1) == ",") {
                        tokens[i] = tokens[i].substr(0, tokens[i].size() - 1);
                    }
                    Graph::Node* in_node = map[tokens[i]];
                    in_node->outputs.push_back(curr_node);
                    curr_node->inputs.push_back(in_node);
                    i++;
                }
                vector<int> function_bits = convert_hex_to_binary(pow(2, curr_node->inputs.size()), tokens[3]);
                assert(function_bits.size() == pow(2, curr_node->inputs.size()));
                curr_node->function_bits = function_bits;
            }
            else {
                // This should not happen
                assert(false);
            }
        }
    }

    return g;
}

// Convertes the graph g into SHDL format and saves it as the given filename + "_SHDL"
void graph_to_shdl(string str_filename, Graph* g) {
    ofstream os;
    os.open(str_filename + "_SHDL");
    int number = 0;
    vector<int> output_numbers;
    for (Graph::Node* v : g->nodes) {
        if (v->type == "input") {
            v->number = number++;
            write_shdl_line(os, v);
        }
    }
    for (Graph::Node* v : g->nodes) {
        write_node_with_copy_gates(os, v, number);
        if (v->type == "output") {
            output_numbers.push_back(v->number);
        }
    }
    os << "outputs ";
    for (int i : output_numbers) {
        os << i << " ";
    }
    os << "\n";

    os.close();
}

// Reduce fanout of graph by using copy gates
void reduceFanOut(Graph* g) {
    for (Graph::Node* v : g->nodes) {
        make_copy_gate_tree(v);
    }
}

// Create shdl circuit description from graph
void parse_bench(string str_filename) {
    parse_bench(str_filename, 1);
}

/*
Converts a .bench file into a SHDL with fanout <= 2 that can be used in our UC compiler. Additionally it is possible
to create a SHDL file consisting of multiple copies of the original .bench file. Inputs and outputs are adopted. There is
no interaction between the copies of the circuit.
*/
void parse_bench(string str_filename, int copies) {
    vector<Graph*> graphs;
    // Create the desired amount of graphs
    for (int i = 0; i < copies;i++) {
        graphs.push_back(benchToGraph(str_filename));
    }
    string outfilename = str_filename.substr(8, str_filename.length() - 8 - 6);
    outfilename = "circuits/" + outfilename;

    // Merge them to one graph
    for (int i = 1; i < copies;i++) {
        for (Graph::Node* v : graphs[i]->nodes) {
            graphs[0]->nodes.push_back(v);
        }
    }

    // Write this graph to SHDL
    graph_to_shdl(outfilename, graphs[0]);

}

// Replaces wires having more than fanout 2 by copy gates
void make_copy_gate_tree(Graph::Node* v) {
    while (v->outputs.size() > 2) {
        v->copy_gates.clear();
        for (uint i = 1; i < v->outputs.size(); i += 2) {
            Graph::Node* copy_gate = new Graph::Node(v->number, "copy_gate", "copy");
            v->copy_gates.push_back(copy_gate);
            int iterations = 2;
            if (i == v->outputs.size() - 1) {
                iterations = 1;
            }
            for (int j = 0; j < iterations;j++) {
                Graph::Node* w = v->outputs[i + j];
                copy_gate->outputs.push_back(w);
                int index = find_index<Graph::Node*>(w->inputs, v);
                w->inputs[index] = copy_gate;
            }
        }
        while (v->outputs.size() > 1) {
            v->outputs.pop_back();
        }
        for (Graph::Node* copy_gate : v->copy_gates) {
            v->outputs.push_back(copy_gate);
            copy_gate->inputs.push_back(v);
        }
    }
}

// Writes node information into a SHDL file
void write_shdl_line(ofstream& os, Graph::Node* v) {
    os << v->number;
    if (v->type == "input") {
        os << " input" << "\n";
    }
    else if (v->type == "gate" || v->type == "output") {
        if (v->type == "output") {
            os << " output";
        }
        os << " gate" << " arity" << " " << v->inputs.size() << " table [ ";
        for (int i : v->function_bits) {
            os << i << " ";
        }
        os << "] ";
        os << "inputs [ ";
        for (Graph::Node* u : v->inputs) {
            os << u->number << " ";
        }
        os << "]" << "\n";
    }
    else if (v->type == "copy") {
        os << " gate arity 1 table [ 0 1 ] ";
        os << "inputs [ ";
        for (Graph::Node* u : v->inputs) {
            os << u->number << " ";
        }
        os << "]" << "\n";
    }
}


// Helper function for copy gates
void write_node_with_copy_gates(ofstream& os, Graph::Node* u, int& number) {
    queue<Graph::Node*> q;
    q.push(u);
    Graph::Node* v;
    while (!q.empty()) {
        v = q.front();
        q.pop();
        if (v->type != "input") {
            v->number = number++;
            write_shdl_line(os, v);
        }
        for (Graph::Node* w : v->outputs) {
            if (w->type == "copy") {
                q.push(w);
            }
        }
    }
}

// Transforms a string in binary format to HEX format up to 4 bits
string binary_gate_to_hex(string gate_functionality) {
    if (gate_functionality == "00") {
        return "0x0";
    }
    if (gate_functionality == "01") {
        return "0x1";
    }
    if (gate_functionality == "10") {
        return "0x2";
    }
    if (gate_functionality == "11") {
        return "0x3";
    }
    if (gate_functionality == "0000") {
        return "0x0";
    }
    if (gate_functionality == "0001") {
        return "0x1";
    }
    if (gate_functionality == "0010") {
        return "0x2";
    }
    if (gate_functionality == "0011") {
        return "0x3";
    }
    if (gate_functionality == "0100") {
        return "0x4";
    }
    if (gate_functionality == "0101") {
        return "0x5";
    }
    if (gate_functionality == "0110") {
        return "0x6";
    }
    if (gate_functionality == "0111") {
        return "0x7";
    }
    if (gate_functionality == "1000") {
        return "0x8";
    }
    if (gate_functionality == "1001") {
        return "0x9";
    }
    if (gate_functionality == "1010") {
        return "0xA";
    }
    if (gate_functionality == "1011") {
        return "0xB";
    }
    if (gate_functionality == "1100") {
        return "0xC";
    }
    if (gate_functionality == "1101") {
        return "0xD";
    }
    if (gate_functionality == "1110") {
        return "0xE";
    }
    if (gate_functionality == "1111") {
        return "0xF";
    }
    assert(false);

}

// Transforms a graph represented in SHDl format to Bench format
void shdl_to_bench(string filepath) {
    ifstream is;
    ofstream os;
    is.open(filepath);
    os.open(filepath + "_bench");
    os << "# Converted from shdl to bench" << "\n";
    string line;
    vector<string> tokens;

    uint num_inputs = 0;
    uint num_gates = 0;
    uint num_outputs = 0;
    vector<int> outputs;
    vector<int> inputs;

    while (getline(is, line)) {
        if (line == "") {
            continue;
        }
        tokenize(line, tokens);
        if (tokens[0] == "outputs") {
            for (uint i = 1; i < tokens.size();i++) {
                outputs.push_back(stoi(tokens[i]));
            }
        }
        else if (tokens[1] == "input") {
            num_inputs++;
            inputs.push_back(stoi(tokens[0]));
        }
        else if (tokens[1] == "gate") {
            num_gates++;
        }
        else if (tokens[1] == "output") {
            num_outputs++;
        }
    }

    assert(num_outputs == outputs.size());
    is.clear();
    is.seekg(0, ios::beg);

    int shift = 0;
    int gate_num = -1;
    int arity = -1;

    for (int in : inputs) {
        os << "INPUT(" << in << ")" << "\n";
    }
    for (int out : outputs) {
        os << "OUTPUT(" << out << ")" << "\n";
    }

    while (getline(is, line)) {
        if (line == "") {
            continue;
        }
        tokenize(line, tokens);
        shift = 0;
        if (tokens[0] != "outputs") {
            gate_num = stoi(tokens[0]);
        }
        if (tokens[1] == "output") {
            shift = 1;
        }
        if (tokens[1 + shift] == "gate") {
            arity = stoi(tokens[3 + shift]);
            int input_nr;
            vector<int> gate_inputs;
            for (int i = 0; i < arity; i++) {
                input_nr = stoi(tokens[tokens.size() - 1 - arity + i]);
                gate_inputs.push_back(input_nr);
            }
            string gate_functionality;
            int start_index = 6 + shift;
            if (arity > 0) {
                for (int i = 0; i < pow(2, gate_inputs.size());i++) {
                    gate_functionality += tokens[start_index + i];
                }
            }
            os << gate_num << " = LUT " << binary_gate_to_hex(gate_functionality) << " ( ";
            for (uint i = 0; i < gate_inputs.size(); i++) {
                os << gate_inputs[i];
                if (i != gate_inputs.size() - 1) {
                    os << " , ";
                }
            }
            os << " )" << "\n";

        }
    }
}



// Creates a graph with the given number of inputs, gates and outputs. Edges are randomly added only in ascending order of the vertices while respecting the maximum in- and outdegree.
// This is not a uniformly random chosen graph.
Graph* create_random_graph(uint num_inputs, uint num_gates, uint num_outputs, uint max_outdegree, uint max_indegree, string filename) {
    uint num_vertices = num_inputs + num_gates + num_outputs;

    // Create graph
    Graph* g = new Graph();
    uint counter = 0;
    for (; counter < num_inputs;counter++) {
        g->nodes.push_back(new Graph::Node(counter, "", "input"));
    }
    for (; counter < num_inputs + num_gates;counter++) {
        g->nodes.push_back(new Graph::Node(counter, "", "gate"));
    }
    for (; counter < num_inputs + num_gates + num_outputs;counter++) {
        g->nodes.push_back(new Graph::Node(counter, "", "output"));
    }

    // Create edges
    using namespace std::chrono;
    auto seed = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count();
    std::mt19937 gen(seed);
    std::uniform_int_distribution<size_t> rand_vertices = std::uniform_int_distribution<size_t>(num_inputs, num_vertices - 1);
    for (uint i = 0; i < num_vertices - num_outputs;i++) {
        for (uint j = 0; j < max_outdegree; j++) {
            uint random_nr = rand_vertices(gen);
            while (random_nr <= i) {
                random_nr = rand_vertices(gen);
            }
            Graph::Node* target = g->nodes[random_nr];
            if (target->inputs.size() < max_indegree) { // if it is higher, ignore this edge
                g->nodes[i]->outputs.push_back(target);
                target->inputs.push_back(g->nodes[i]);
            }
        }
    }
    // Set function bits
    std::uniform_int_distribution<size_t> rand;
    for (uint i = num_inputs; i < num_vertices; i++) {
        size_t arity = g->nodes[i]->inputs.size();
        rand = std::uniform_int_distribution<size_t>(0, pow(2, arity) - 1);
        uint64_t gate_function = rand(gen);
        vector<int> binary_rep = get_binary(pow(2, arity), gate_function);
        assert(binary_rep.size() == pow(2, arity));
        g->nodes[i]->function_bits = binary_rep;
    }

    graph_to_shdl(filename, g);
    return g;
}

