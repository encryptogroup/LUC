#include "gamma.h"

DAG::DAG() {}

DAG::DAG(int size) {
    for (int i = 0; i < size;i++) {
        DAG::Node* v = new Node();
        v->type = "undefined";
        v->number = i + 1;
        vertices.push_back(v);
    }
}
DAG::Edge::Edge(DAG::Node* from, DAG::Node* to,int from_slot, int to_slot) {
    this->from = from;
    this->to = to;
    this->from_slot = from_slot;
    this->to_slot = to_slot;
}

void DAG::add_edge(DAG::Node* from, DAG::Node* to,int from_slot, int to_slot) {
    DAG::Edge* e = new DAG::Edge(from, to,from_slot, to_slot);
    
    from->out_edges.push_back(e);
    
    to->in_edges.push_back(e);
}

// Parses the given SHDl file into a DAG
DAG* read_SHDL_to_Gamma(string str_filename) {
    ifstream is;
    is.open(str_filename);

    // Count number of needed nodes in the DAG and create the DAG
    string line;
    vector<string> tokens;

    DAG* g = new DAG();

    // this maps an edge number to a Node and a slot number
    unordered_map<int, std::tuple<DAG::Node*,int>> mapping;
    int shift = 0;
    int number = 1;
    vector<int> out_edge_nums;
    int arity = -1;
    while (getline(is, line)) {
        if (line == "") {
            continue;
        }
        out_edge_nums.clear();
        tokenize(line, tokens);
    	int t = 0;
        shift = 0;
        if (tokens[0] == "outputs") { // must be always the last line in the shdl file
            for (uint i = 0; i < tokens.size() - 1; i++) {
                int num = stoi(tokens[1 + i]);
                auto [gate, gateslot] = mapping[num];
                DAG::Node* output = new DAG::Node();
                g->vertices.push_back(output);
                output->number = number++;
                output->type = "output";
                g->add_edge(gate, output,gateslot,0);
            }
        }
        else {
        
            while(t<tokens.size())
            {
            	if(tokens[t] == "input" || tokens[t] == "gate" || tokens[t] == "outputs" || tokens[t] == "output" ) break;
            	int token = 0;
            	token = stoi(tokens[t]);
            	out_edge_nums.push_back(token);
            	t++;
            }
        }
        if (tokens[t] == "input") {
            DAG::Node* current = new DAG::Node();
            current->number = number++;
            current->type = "input";
            // an input always just has the singular slot
            mapping[out_edge_nums[0]] = std::make_tuple(current,0);
            g->vertices.push_back(current);
        }
        if (tokens[t] == "output") {
            shift = 1;
        }
        if (tokens[t + shift] == "gate") {
            DAG::Node* current = new DAG::Node();
            g->vertices.push_back(current);
            current->number = number++;
            current->type = "gate";
            
            int num_slots = 0;
            
            for(int g: out_edge_nums)
            {
            	mapping[g] = std::make_tuple(current,num_slots);
            	num_slots++;
            	if(num_slots > 4)
            	{
            	
            	//cout << number << "\n";
            	//cout << "Slots: " << num_slots << "\n";
            	}
            }
            
            arity = stoi(tokens[t + 2 + shift]);
            int input_nr;
            DAG::Node* input;
            int num_inputs = 0;
            for (int i = 0; i < arity; i++) {
                input_nr = stoi(tokens[tokens.size() - 1 - arity + i]);
                auto [input,inputslot] = mapping[input_nr];
                
                g->add_edge(input, current,inputslot,num_inputs);
                num_inputs++;
            }
            int start_index = t + 5 + shift;
            for (int j = 0; j < num_slots;j++)
            {
            	vector<int> slot_bits;
            	if (arity > 0) {
                	for (int i = 0; i < pow(2, num_inputs);i++) {
                		int bitToken = stoi(tokens[start_index+i]);
                    		slot_bits.push_back(bitToken);
                	}
            	}
            	current->function_bits.push_back(slot_bits);
            	start_index = start_index + 2 + pow(2, num_inputs);
            }

        }
    }
    
    // Order outgoing edges by slot number
    for(DAG::Node* v: g->vertices)
    {
    
    		sort (v->out_edges.begin(),v->out_edges.end(), [ ]( const auto& lhs, const auto& rhs )
		{
   		return lhs->from_slot < rhs->from_slot;
		});
    
    }
    
    return g;
}

// Returns the node in the DAG with the given number
DAG::Node* DAG::get_node(int nr) {
    for (DAG::Node* v : vertices) {
        if (v->number == nr) {
            return v;
        }
    }
    cerr << "nr " << nr << " doesn't exist in graph!" << endl;
    assert(false);
    return 0;
}


//Creates a copy of the DAG with copies of the nodes of the original DAG without edges
DAG* DAG::clone_DAG() {
    DAG* g = new DAG();
    for (DAG::Node* v : vertices) {
        DAG::Node* v_clone = new DAG::Node();
        v_clone->number = v->number;
        v_clone->type = v->type;
        v_clone->function_bits = v->function_bits;
        g->vertices.push_back(v_clone);
    }
    return g;
}

// Creates a bipartite graph out of this DAG
// This is done like in the coloring theorem used to seperate the graph into Gamma1 graphs
DAG* DAG::create_bipartite() {
    DAG* g = new DAG();
    unordered_map<int, DAG::Node*> clones1;
    unordered_map<int, DAG::Node*> clones2;
    for (DAG::Node* v : vertices) {
        DAG::Node* v_clone1 = new DAG::Node();
        v_clone1->number = v->number;
        v_clone1->type = v->type;
        v_clone1->function_bits = v->function_bits;
        DAG::Node* v_clone2 = new DAG::Node();
        v_clone2->number = v->number;
        v_clone2->type = v->type;
        v_clone2->function_bits = v->function_bits;
        g->vertices.push_back(v_clone1);
        g->vertices.push_back(v_clone2);
        clones1[v->number] = v_clone1;
        clones2[v->number] = v_clone2;
    }
    for (DAG::Node* v : vertices) {
        DAG::Node* from_clone1 = clones1[v->number];
        DAG::Node* to_clone2;
        
        
        for (DAG::Edge* e : v->out_edges) {
            to_clone2 = clones2[e->to->number];
            g->add_edge(from_clone1, to_clone2,e->from_slot,e->to_slot);
        }
    }
    return g;
}

void DAG::print_graph(string name) {
    string filename = "graphviz/" + name;
    ofstream os;
    os.open(filename);
    os << "digraph{\n";
    os << "graph [pad=\"0.5\", nodesep=\"1\", ranksep=\"2\"] \n";
    for (DAG::Node* v : vertices) {
        os << "node " << v->get_graphviz_style() << " \"" << v->number << "\";\n";
    }
    
    for (DAG::Node* v : vertices) {
    
    	
    	
        for (DAG::Edge* e : v->out_edges) {
            DAG::Node* w = e->to;
            os << v->number << " -> " << w->number;
            os << " [label=\"";
            os << e->from_slot;
            os << " -> ";
            os << e->to_slot;
            os << "\"] \n";
        }
    }
    os << "}";
    os.close();
}

string DAG::Node::get_graphviz_style() {
    if (type == "input") {
        return "[ style=filled,fillcolor=\"lawngreen\" ]";
    }
    else if (type == "gate") {
        return "[ style=filled,fillcolor=\"yellow\" ]";
    }
    else if (type == "output") {
        return "[ style=filled,fillcolor=\"darkgreen\" ]";
    }
    else if (type == "undefined") {
        return "[ style=filled,fillcolor=\"white\" ]";
    }
    else {
        // Should not happen
        assert(false);
        return "";
    }
}

// Returns an uncolored edge. If there is none, 0 is returned
DAG::Edge* find_uncolored_edge(unordered_map<DAG::Edge*, int>& edge_colors) {
    for (pair<DAG::Edge*, int> entry : edge_colors) {
        if (entry.second == -1) {
            return entry.first;
        }
    }
    return 0; // If there is no uncolored edge
}

// Finds the colors alpha and beta like in the coloring theorem
pair<pair<int, int>, DAG::Edge*> find_color(unordered_map<DAG::Edge*, int>& edge_colors, DAG::Edge* e, int colors) {
    // Note that u only has outgoing edges and v only has ingoing edges
    DAG::Node* u = e->from;
    DAG::Node* v = e->to;
    int alpha = -1;
    int beta = -1;
    DAG::Edge* e_ret;
    
    for (DAG::Edge* e_u : u->out_edges) {
        if (e_u == e) {
            continue;
        }
        beta = edge_colors[e_u];
        // should not be -1
        if (beta == -1) {
            continue;
        }
        bool beta_used = false;
        for (DAG::Edge* e_v : v->in_edges) {
            if (e_v == e) {
                continue;
            }
            else if (edge_colors[e_v] == beta) {
                beta_used = true;
                break;
            }
        }
        if (!beta_used) {
            e_ret = e_u;
            break;
        }
    }
    // exclude used colors for alpha
    vector<bool> alpha_candidates(colors, true);
    
    
    for (DAG::Edge* e_u : u->out_edges) {
        if (edge_colors[e_u] != -1) {
            alpha_candidates[edge_colors[e_u]] = false;
        }
    }
    
    for (uint i = 0; i < alpha_candidates.size(); i++) {
        if (alpha_candidates[i]) {
            alpha = i;
        }
    }
    assert(alpha != -1);
    assert(beta != -1);
    return make_pair(make_pair(alpha, beta), e_ret);
}

// Finds a color that can be used to color this edge.
// If no color is found, -1 is returned.
int find_free_color(unordered_map<DAG::Edge*, int>& edge_colors, DAG::Edge* e, int colors) {
    DAG::Node* u = e->from;
    DAG::Node* v = e->to;
    // exclude used colors
    int color = -1;
    vector<bool> candidates(colors, true);
    
    
    for (DAG::Edge* e_u : u->out_edges) {
        if (edge_colors[e_u] != -1) {
            candidates[edge_colors[e_u]] = false;
        }
    }
    
    for (DAG::Edge* e_v : v->in_edges) {
        if (edge_colors[e_v] != -1) {
            candidates[edge_colors[e_v]] = false;
        }
    }
    for (uint i = 0; i < candidates.size(); i++) {
        if (candidates[i]) {
            color = i;
        }
    }
    return color;
}

// Colors the longest possible beta-alpha alternating path starting from e like in the coloring theorem
void DAG::color_path(unordered_map<DAG::Edge*, int>& edge_colors, DAG::Edge* e, int alpha, int beta) {
    vector<DAG::Edge*> path;
    vector<int> alpha_beta = { alpha, beta };
    int next_color = 0;
    DAG::Edge* curr = e;
    DAG::Node* curr_node = e->from;
    DAG::Node* next_node;
    while (curr) {
        path.push_back(curr);
        bool side;
        vector<DAG::Edge*> adjacent_edges;
        if (curr->from == curr_node) {
            side = false;
        }
        else {
            side = true;
        }
        if (side) {
            next_node = curr->from;
            adjacent_edges = next_node->out_edges;
        }
        else {
            next_node = curr->to;
            adjacent_edges = next_node->in_edges;
        }
        curr = 0;
        for (DAG::Edge* e_next : adjacent_edges) {
            if (edge_colors[e_next] == alpha_beta[next_color]) {
                curr = e_next;
                curr_node = next_node;
                next_color = (next_color + 1) % 2;
                break;
            }
        }
    }

    // Now swap colors on the path
    for (DAG::Edge* r : path) {
        if (edge_colors[r] == alpha) {
            edge_colors[r] = beta;
        }
        else if (edge_colors[r] == beta) {
            edge_colors[r] = alpha;
        }
        else {
            // should not happen
            assert(false);
        }
    }
}

// Colors the bipartite graph like in the proof of the coloring theorem. Returns the edge sets, where each edge set has the same color in a vector
vector<vector<DAG::Edge*>> DAG::color_graph(int colors) {
    unordered_map<DAG::Edge*, int> edge_colors;
    for (DAG::Node* v : vertices) {
    	
        for (DAG::Edge* e : v->out_edges) {
            edge_colors[e] = -1;
        }
    }

    DAG::Edge* e = find_uncolored_edge(edge_colors);

    while (e) {
        int color = find_free_color(edge_colors, e, colors);
        if (color != -1) {
            edge_colors[e] = color;

        }
        else {
            pair<pair<int, int>, DAG::Edge*> alpha_beta_e = find_color(edge_colors, e, colors);
            int alpha = alpha_beta_e.first.first;
            int beta = alpha_beta_e.first.second;
            DAG::Edge* r = alpha_beta_e.second;
            assert(alpha != -1);
            assert(beta != -1);
            assert(r->from == e->from);
            color_path(edge_colors, r, alpha, beta);
            edge_colors[e] = beta;
        }
        e = find_uncolored_edge(edge_colors);
    }

    vector<vector<DAG::Edge*>> color_sets(colors, vector<DAG::Edge*>());
    for (pair<DAG::Edge*, int> entry : edge_colors) {
        assert(entry.second != -1);
        color_sets[entry.second].push_back(entry.first);
    }
    return color_sets;
}

// Splits a Gamma_k graph into k Gamma_1 graphs
vector<DAG*> DAG::split_into_gamma1(int nr_of_graphs) {
    assert(nr_of_graphs >= 2);
    uint max_indegree = 0;
    uint max_outdegree = 0;
    uint max_degree = 0;
    for (DAG::Node* v : vertices) {
        if (v->in_edges.size() > max_indegree) {
            max_indegree = v->in_edges.size();
        }
        if (v->out_edges.size() > max_outdegree) {
            max_outdegree = v->out_edges.size();
        }
    }
    max_degree = (max_indegree > max_outdegree) ? max_indegree : max_outdegree;
    DAG* bipartite = create_bipartite();
    vector<DAG*> dag1s;
    vector<vector<DAG::Edge*>> edge_sets = bipartite->color_graph(max_degree);
    for (vector<DAG::Edge*> edge_set : edge_sets) {
        DAG* dag1 = clone_DAG();
        for (DAG::Edge* e : edge_set) {
            dag1->add_edge(dag1->get_node(e->from->number), dag1->get_node(e->to->number),e->from_slot,e->to_slot);
        }
        dag1s.push_back(dag1);
    }
    // Pad the output with empty graphs and same node set to get desired number of graphs
    for (int i = dag1s.size(); i < nr_of_graphs; i++) {
        dag1s.push_back(clone_DAG());
    }
    return dag1s;
}

// Returns basic information about the graph
vector<uint> DAG::get_stats() {
    uint num_inputs = 0;
    uint num_gates = 0;
    uint num_outputs = 0;
    for (DAG::Node* v : vertices) {
        if (v->type == "input") {
            num_inputs++;
        }
        else if (v->type == "gate") {
            num_gates++;
        }
        else if (v->type == "output") {
            num_outputs++;
        }
    }
    uint max_indegree = 0;
    uint max_outdegree = 0;
    uint max_degree = 0;
    uint wires = 0;
    for (DAG::Node* v : vertices) {
        wires += v->in_edges.size();
        if (v->in_edges.size() > max_indegree) {
            max_indegree = v->in_edges.size();
        }
        if (v->out_edges.size() > max_outdegree) {
            max_outdegree = v->out_edges.size();
        }
    }
    double avg_degree = (double) wires / (double) vertices.size();
    max_degree = (max_indegree > max_outdegree) ? max_indegree : max_outdegree;
    cout << "Wire count: " << wires << "    avg degree: " << avg_degree << "\n";
    cout << "Inputs: " << num_inputs << "    Gates: " << num_gates << "    Outputs: " << num_outputs << "\n";
    cout << "Max indegree: " << max_indegree << "    Max outdegree: " << max_outdegree << "    Max degree: " << max_degree << endl;

    return vector<uint> {num_inputs, num_gates, num_outputs, max_indegree, max_outdegree, max_degree};
}



DAG::Node* DAG::create_recursive_slot_tree(vector<DAG::Node*> nodes_to_add,uint max_outdegree)
{
	vector<DAG::Node*> copy_gates;
	int needed_nodes = 0;
	while(needed_nodes*max_outdegree < nodes_to_add.size()) 
	{
		needed_nodes++;
	}
	cout << "Needed copy gates: "<<needed_nodes<<" for " << nodes_to_add.size() << " outgoing nodes\n";
	
	int children_added = 0;
	for(int i = 0; i< needed_nodes; i++)
	{
		DAG::Node* copy_gate = new DAG::Node();
		copy_gate->type = "copy";
		vector<int> bits;
		bits.push_back(0);
		bits.push_back(1);
		copy_gate->function_bits.push_back(bits);
		copy_gates.push_back(copy_gate);
		int j = 0;
		while(j<max_outdegree && (children_added + j) < nodes_to_add.size())
		{
			cout << "Adding " << j+children_added << " to "<< i << "\n";
			add_edge(copy_gate,nodes_to_add[j+children_added],0,0);
			j++;
		}
		children_added = children_added + j;
	}
	if(copy_gates.size() == 1)
	{
		return copy_gates[0];
	}else
	{
		return create_recursive_slot_tree(copy_gates,max_outdegree);
	}
}

vector<DAG::Node*> DAG::add_copy_gate_tree_rec(DAG::Node* v, uint l, uint max_outdegree, uint curr){
    vector<DAG::Node*> ret;
    if(curr > l){
        return ret;
    }
    for(uint i=0; i < max_outdegree;i++){
        DAG::Node* copy_gate = new DAG::Node();
        copy_gate->type = "copy";
        vector<int> new_fb;
        new_fb.push_back(0);
        new_fb.push_back(1);

        copy_gate->function_bits.push_back(new_fb);
        DAG::Edge* e_copy = new Edge(v, copy_gate,0,0);
        v->out_edges.push_back(e_copy);
        copy_gate->in_edges.push_back(e_copy);
        if (curr == l){
            ret.push_back(copy_gate);
        }
    }
    curr++;
    for(DAG::Edge* e: v->out_edges){
        vector<DAG::Node*> ret_rec = add_copy_gate_tree_rec(e->to,l,max_outdegree,curr);
        for(DAG::Node* c: ret_rec){
            ret.push_back(c);
        }
    }
    return ret;
}


vector<DAG::Node*> DAG::add_copy_gate_tree(DAG::Node* v, uint l, uint max_outdegree){
    vector<DAG::Node*> ret = add_copy_gate_tree_rec(v,l,max_outdegree,2);
    assert(ret.size() == pow(max_outdegree,l-1));
    return ret;
}


// Replaces edges with an outdegree exceeding the maximum outdegree by copy gates
void DAG::make_copy_gate_tree2(unordered_map<DAG::Node*, vector<DAG::Node*>>& all_copy_gates, DAG::Node* v, uint max_outdegree) {
    uint d = v->out_edges.size(); // needed number of outgoing wires
    if (d <= max_outdegree){
        return; // outdegree is not larger than allowed => OK
    } else{
        vector<DAG::Edge*> neighbor_edges;
        for (DAG::Edge* e: v->out_edges){
            neighbor_edges.push_back(e);
        }
        v->out_edges.clear();
        int l = 1;
        while (pow(max_outdegree,l) < d){
            l++;
        }
        vector<DAG::Node*> tmp_copy_gates = add_copy_gate_tree(v,l,max_outdegree);
        assert(tmp_copy_gates.size() == pow(max_outdegree,l-1));
        vector<DAG::Node*> copy_gates;
        uint x = 0;
        while(pow(max_outdegree,l-1) + x*(max_outdegree-1) < d){
            x++;
        }
        uint k = 0;
        for(uint i=0; i < x;i++){
            for (uint j=0; j < max_outdegree;j++){
                if (k == d - pow(max_outdegree,l-1) + x){
                    break;
                }
                DAG::Edge* e_copy = new Edge(tmp_copy_gates[i], neighbor_edges[k]->to,0,neighbor_edges[k]->to_slot);
                tmp_copy_gates[i]->out_edges.push_back(e_copy);
                int index = find_index<DAG::Edge*>(neighbor_edges[k]->to->in_edges,neighbor_edges[k]);
                neighbor_edges[k]->to->in_edges[index] = e_copy;
                copy_gates.push_back(tmp_copy_gates[i]);
                k++;
            }
        }
        for(uint i = x; i < pow(max_outdegree,l-1); i++){
            assert(tmp_copy_gates[i]->in_edges.size() == 1);
            DAG::Node* copy_gate = tmp_copy_gates[i]->in_edges[0]->from;
            int index2 = find_index<DAG::Edge*>(copy_gate->out_edges, tmp_copy_gates[i]->in_edges[0]);
            tmp_copy_gates[i]->in_edges.clear();
            DAG::Edge* e_copy = new Edge(copy_gate, neighbor_edges[k]->to,0,neighbor_edges[k]->to_slot);
            copy_gate->out_edges[index2] = e_copy;
            int index = find_index<DAG::Edge*>(neighbor_edges[k]->to->in_edges, neighbor_edges[k]);
            neighbor_edges[k]->to->in_edges[index] = e_copy;
            copy_gates.push_back(copy_gate);
            k++;
        }
        assert(copy_gates.size() == d);
        return;
    }
}



// Replaces edges with an outdegree exceeding the maximum outdegree by copy gates
// copy gates only have one outslot 0
void DAG::make_copy_gate_tree(unordered_map<DAG::Node*, vector<DAG::Node*>>& all_copy_gates, DAG::Node* v, uint max_outdegree) {
    vector<DAG::Node*> copy_gates;
    int max_slot = 0;
    
    for(DAG::Edge* e: v->out_edges)
    {
    	int s = e->from_slot;
    	if(max_slot < s)
    	{
    		max_slot = s;
    	}
    
    }
    
    if(v->out_edges.size()<max_outdegree)
    {
    return;
    }
    if(max_outdegree < max_slot+1)
    {
    cerr << "cannot reduce gate "<< v->number <<" with " << max_slot+1 << " distinct outputs to fanout "<< max_outdegree << "\n";
    exit(1);
    }
    vector<DAG::Edge*> edges = v->out_edges;
    vector<DAG::Edge*> new_edges;
    v->out_edges = new_edges;
    for(int s = 0; s < max_slot+1;s++)
    {
    	vector<DAG::Node*> slot_nodes;
    	for(DAG::Edge* e: edges)
    	{
    		if(s == e->from_slot)
    			slot_nodes.push_back(e->to);
    	}
    	auto slot_node = create_recursive_slot_tree(slot_nodes, max_outdegree);
    	add_edge(v,slot_node,s,0);
    }
    
}




// Helper function to add copy gates to the graph
void add_vertices(vector<DAG::Node*>& new_vertices, DAG::Node* u, int& number) {
    queue<DAG::Node*> q;
    q.push(u);
    DAG::Node* v;
    while (!q.empty()) {
        v = q.front();
        q.pop();
        if (v->type != "input") {
            if (v->type == "copy") { v->type = "gate"; }
            v->number = number++;
            new_vertices.push_back(v);
        }
        
        for (DAG::Edge* e : v->out_edges) {
            DAG::Node* w = e->to;
            if (w->type == "copy") {
                q.push(w);
            }
        }
    }
}

void DAG::reduce_fan_out2(uint max_outdegree) {
    for (DAG::Node* v : vertices) {
        unordered_map<DAG::Node*, vector<DAG::Node*>> copy_gates;
        //make_copy_gate_tree(copy_gates, v, max_outdegree);
        make_copy_gate_tree2(copy_gates, v, max_outdegree);
    }
    vector<DAG::Node*> new_vertices;
    int number = 1;
    for (DAG::Node* v : vertices) {
        if (v->type == "input") {
            v->number = number++;
            new_vertices.push_back(v);
        }
    }
    for (DAG::Node* v : vertices) {
        // Now add vertex, then all its copy gates and then next vertex and so on
        // Change number accordingly
        add_vertices(new_vertices, v, number);
    }
    vertices = new_vertices;
}

// Reduced the fanout of the graph to the given maximum by using copy gates
void DAG::reduce_fan_out(uint max_outdegree) {
    for (DAG::Node* v : vertices) {
        unordered_map<DAG::Node*, vector<DAG::Node*>> copy_gates;
        make_copy_gate_tree(copy_gates, v, max_outdegree);
    }
    vector<DAG::Node*> new_vertices;
    int number = 1;
    for (DAG::Node* v : vertices) {
        if (v->type == "input") {
            v->number = number++;
            new_vertices.push_back(v);
        }
    }
    for (DAG::Node* v : vertices) {
        // Now add vertex, then all its copy gates and then next vertex and so on
        // Change number accordingly
        add_vertices(new_vertices, v, number);
    }
    vertices = new_vertices;
}


//Removes outgoing wires that with the same input and replaces them with duplicates
void DAG::remove_double_wire_usages()
{
	for(DAG::Node* v : vertices) {
		if(v->type == "gate")
		{
		int i = 1;
		for(int x = 0; x < v->out_edges.size(); x++)
		{
			int max_slot = v->out_edges[v->out_edges.size()-1]->from_slot;
			auto e = v->out_edges[x];
			for(int y = x + 1; y < v->out_edges.size();y++)
			{
				auto f = v->out_edges[y];
			
				
				if(e != f && (e->from_slot == f->from_slot))
				{
				
					f->from_slot = max_slot + i;
					i++;
					auto t = v->function_bits[e->from_slot];
					v->function_bits.push_back(t);
				}
			}
		}
		}
	}
	
	
    // Order outgoing edges by slot number
    for(DAG::Node* v: vertices)
    {
    
    		sort (v->out_edges.begin(),v->out_edges.end(), [ ]( const auto& lhs, const auto& rhs )
		{
   		return lhs->from_slot < rhs->from_slot;
		});
    }
	
}


// Transform DAG to split A->B LUT into B A->1 LUTs
vector<pair<DAG::Node*,DAG::Node*>>  DAG::transform_fixed_multi_pole_auxiliary_graph() 
{
    vector<pair<DAG::Node*,DAG::Node*>> outputpole_mapping;
    int count = 0;
    vector<DAG::Node*> new_vertices;

    vector<DAG::Node*> new_dummy_outputs;

    vector<DAG::Edge*> first_out_edges;

    int maximum_number_of_different_outputs = 0;



    for(DAG::Node* v : vertices)
    {
        for(DAG::Edge* e : v->out_edges)
            {
                if(e->from_slot > maximum_number_of_different_outputs)
                {
                    maximum_number_of_different_outputs = e->from_slot;
                   // cout << e->from_slot<< "\n";
                }
            }

    }
    cout << "Every node has: " << maximum_number_of_different_outputs +1 << " different outputs\n";
    for(DAG::Node* v : vertices)
    {
        uint largest_output = 0;
       if(v->type == "gate")
       {
            for(DAG::Edge* e : v->out_edges)
            {
                if(e->from_slot == 0)
                    first_out_edges.push_back(e);
                if(e->from_slot > largest_output)
                {
                    largest_output = e->from_slot;
                }
            }

            new_vertices.push_back(v);
            for(int i = 0; i < largest_output;i++)
            {
                DAG::Node* gate_output_pole_node = new DAG::Node();
                gate_output_pole_node->type = "gate";
                gate_output_pole_node->function_bits.push_back(v->function_bits[i+1]);

                new_vertices.push_back(gate_output_pole_node);
                for(DAG::Edge* e : v->out_edges)
                {
                    if(e->from_slot == i + 1)
                    {
                        gate_output_pole_node->out_edges.push_back(e);
                        e->from = gate_output_pole_node;
                        e->from_slot = 0;
                    }
                }
                outputpole_mapping.push_back(make_pair(gate_output_pole_node,v));
            }


            // add extra outputs such that all have the same size
            for(int i = largest_output; i < maximum_number_of_different_outputs;i++)
            {
                DAG::Node* gate_output_pole_node = new DAG::Node();
                gate_output_pole_node->type = "gate";
                gate_output_pole_node->function_bits.push_back(v->function_bits[0]);

                new_vertices.push_back(gate_output_pole_node);


                outputpole_mapping.push_back(make_pair(gate_output_pole_node,v));
            }



            auto copy = v->function_bits[0];
            v->function_bits.clear();
            /*
            for(auto x : copy)
            {
                cout << x << "\n";
            }
            */
            v->function_bits.push_back(copy);
            // First gate only has outgoing edges with slot number 0
            v->out_edges = first_out_edges;
            first_out_edges.clear();
       }else{
            new_vertices.push_back(v);
       }
       count++;
    }
    
    vertices = new_vertices;

    for(auto output : new_dummy_outputs)
    {
        vertices.push_back(output);
    }

    for(int i = 0;i<vertices.size();i++)
    {
        vertices[i]->number = i+1;
    }
    return outputpole_mapping;
}



// Creates the auxiliary graph to use dynamic multi-input gates.
// max_outdegree is the number of the maximum allowed fanout
pair< DAG*, pair < unordered_map<int, int> ,  pair < unordered_map<int, vector<int> > ,  unordered_map<int, vector<int> > >  > >   DAG::transform_in_place_graph(uint max_outdegree) {
    DAG* g = new DAG();
    int number = 1;
    unordered_map<int, int> pole_mapping;
    
    
    unordered_map<int, vector<int>> in_forwarding_poles;
    unordered_map<int, vector<int>> out_forwarding_poles;
    vector<DAG::Node*> clones;
    unordered_map<int,int> in_usages;
    unordered_map<int,int> out_usages;
    vector<uint> needed_input_gate_forwards;
    
    for (DAG::Node* v : vertices) {
    	if(v->type == "input")
    	{
    	DAG::Node* v_clone = new DAG::Node();
        clones.push_back(v_clone);
        v_clone->type = v->type;
        v_clone->function_bits = v->function_bits;
        number = number;
        v_clone->number = number++;
        pole_mapping[v->number] = v_clone->number;
        in_usages[v->number] = 0;
        out_usages[v->number] = 0;
        g->vertices.push_back(v_clone);
        
        uint needed_out_forwarding_poles = (v->out_edges.size() > max_outdegree) ? ceil((double)v->out_edges.size() / max_outdegree) - 1 : 0;
        
        needed_input_gate_forwards.push_back(needed_out_forwarding_poles);
         
        
    	}
    }
    int inputforward_number = 0;
    for(auto needed_out_forwarding_poles : needed_input_gate_forwards ) {
    	inputforward_number++;
    	if (needed_out_forwarding_poles > 0) {
            for (uint i = 0; i < needed_out_forwarding_poles;i++) {
                DAG::Node* forwarding_pole = new DAG::Node();
                forwarding_pole->type = "gate";
                forwarding_pole->number = number;
                number++;
                
                out_forwarding_poles[inputforward_number].push_back(forwarding_pole->number);
                g->vertices.push_back(forwarding_pole);
            }
        }
    }
    
    for (DAG::Node* v : vertices) {
    
    // first create in poles reducing
    	if(v->type != "input"){
    
        uint needed_in_forwarding_poles = (v->in_edges.size() > max_outdegree) ? ceil((double)v->in_edges.size() / max_outdegree) - 1 : 0;
        
        
        //  first out edge stays with first clone, note that every pole  currently can only have one outgoing edge in reduced approach
        uint needed_out_forwarding_poles = (v->out_edges.size() > max_outdegree) ? ceil((double)v->out_edges.size() / max_outdegree) - 1 : 0;
        
        
        
        DAG::Node* v_clone = new DAG::Node();
        clones.push_back(v_clone);
        v_clone->type = v->type;
        v_clone->function_bits = v->function_bits;
        number = needed_in_forwarding_poles + number;
        v_clone->number = number++;
        pole_mapping[v->number] = v_clone->number;
        in_usages[v->number] = 0;
        out_usages[v->number] = 0;
        if (needed_in_forwarding_poles > 0) {
            for (uint i = 0; i < needed_in_forwarding_poles;i++) {
                DAG::Node* forwarding_pole = new DAG::Node();
                forwarding_pole->type = "gate";
                forwarding_pole->number = number - needed_in_forwarding_poles - 1 + i;
                
                in_forwarding_poles[v_clone->number].push_back(forwarding_pole->number);
                g->vertices.push_back(forwarding_pole);
            }
        }
        
        g->vertices.push_back(v_clone);
        
         if (needed_out_forwarding_poles > 0) {
            for (uint i = 0; i < needed_out_forwarding_poles;i++) {
                DAG::Node* forwarding_pole = new DAG::Node();
                forwarding_pole->type = "gate";
                forwarding_pole->number = number;
                number++;
                
                out_forwarding_poles[v_clone->number].push_back(forwarding_pole->number);
                g->vertices.push_back(forwarding_pole);
            }
        }
        
        
        }
        
    }
    
    
    int x = 0;
    
    for (DAG::Node* v : vertices) {
    auto v_clone = g->vertices[pole_mapping[v->number] - 1];
    x++;
    for (DAG::Edge* e_in : v->in_edges) {
    	
        
            DAG::Node* from_clone = g->vertices[pole_mapping[e_in->from->number] - 1];
            
            DAG::Node* from_node;
            DAG::Node* to_node;
            if(out_usages[e_in->from->number] < max_outdegree)
            {
            from_node = from_clone;
            }else
            {
            int p = floor((double) out_usages[e_in->from->number] / max_outdegree) - 1;
            int forward_pole_nr = out_forwarding_poles[from_clone->number][p];
            DAG::Node* forwarding_pole = g->vertices[forward_pole_nr - 1];
            from_node = forwarding_pole;
            }
            
            
            
            
            
            if (in_usages[e_in->to->number] < max_outdegree) {
            	// Not sure about the slot choice here
            	to_node = v_clone;
            }
            else {
                int forward_nr = floor((double) in_usages[e_in->to->number] / max_outdegree) - 1;
            	int forward_pole_nr = in_forwarding_poles[v_clone->number][forward_nr];
                DAG::Node* forwarding_pole = g->vertices[forward_pole_nr - 1];
            	to_node = forwarding_pole;
            }
            
            g->add_edge(from_node, to_node, e_in->from_slot,e_in->to_slot);
            
            in_usages[e_in->to->number] = in_usages[e_in->to->number] + 1;
            out_usages[e_in->from->number] = out_usages[e_in->from->number] + 1;
            
        }
        
    }
    
    return make_pair(g, make_pair(pole_mapping , make_pair( in_forwarding_poles, out_forwarding_poles ) ));

}
