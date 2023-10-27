#include <cstdint>
#include <string>
#include <iostream>
#include <cstring>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <unistd.h>
#include <unordered_set>
#include <random>
#include <chrono>
#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <getopt.h>
#include <filesystem>
#include <chrono>


#include "uc/2way/valiant.h"
#include "uc/2way/liu.h"
#include "uc/2way/valiantMerged.h"
#include "util/parseBench.h"
#include "util/utility.h"


// Helper function that seperates a string into a vectopr seperated by a delimiter
void tokenize2(const string& str, vector<string>& tokens) {
	tokens.clear();
    char delimiter = '_';
	string::size_type last_pos = str.find_first_not_of(delimiter, 0);
	string::size_type pos = str.find_first_of(delimiter, last_pos);
	while (string::npos != pos || string::npos != last_pos) {
		tokens.push_back(str.substr(last_pos, pos - last_pos).c_str());
		last_pos = str.find_first_not_of(delimiter, pos);
		pos = str.find_first_of(delimiter, last_pos);
	}
}

// Helper function to parse the filepath
vector<string> parse_filename(string path){
    vector<string> tokens;
    tokenize2(path, tokens);
    return tokens;

}

// Saves basic properties of the UC into a given text file
void save_results(string result_filename, string circuit_filename, string algorithm, bool in_place,uint xgates,uint ygates, uint fanout, pair<vector<ulong>,vector<ulong>> eug_stats, vector<uint> dag_sizes, string circuit_name = "none", uint circuit_lut_size = 0){
    bool newResultFile = !std::filesystem::exists(result_filename);
    ofstream os;
    os.open(result_filename, std::ios_base::app);
    
    if(newResultFile)
    {
    os << "circ" << "\t" << "circ_lut_s" << "\t" << "circ_f" << "\t" << "eug_algo" << "\t" << "dyn" << "\t"
    << "fanout" << "\t" << "A" << "\t" << "B" << "\t" << "C" << "\t" << "uc_s" << "\t" << "eug_s" << "\t" << "x" << "\t" << "y" << "\t" << "uluts" << endl; 
    }
    
    os << circuit_name << "\t" << circuit_lut_size << "\t" << circuit_filename << "\t" << algorithm << "\t" << in_place << "\t" << fanout << "\t" 
        << dag_sizes[0] << "\t" << dag_sizes[1] << "\t" << dag_sizes[2] << "\t" << eug_stats.first[0] << "\t" << eug_stats.first[1] << "\t";
        
    os << xgates;
    os << "\t" << ygates <<  "\t";
    for(uint i = 0; i < eug_stats.second.size(); i++){
        os << eug_stats.second[i];
        if (i != eug_stats.second.size()-1){
            os << ":";
        }
    }
    os << endl;
}


/*
Creates the UC and its programming bits for a given circuit
input_filename is the path to the circuit in Bench or SHDL format
algorithm decides which EUG/UC algorithm to use, options are liu and valiant
in_place = true uses dynamic / in-place multi-input-output gates, otherwise sufficiently many EUGs are merged to achieve this
fanout decides to which fanout the circuit is reduced
copies allows to use duplicate the input circuit if it is given in Bench format
correctness_check toggles the correctness check of the EUG and UC
input_circuit_name is the name displayed in the benchmarks.txt file
circuit_lut_size is the used LUT size for the circuit that is saved in benchmarks.txt
*/
ValiantMerged* create_UC(string input_filename, string algorithm, bool in_place, uint fanout, int copies, bool correctness_check, bool strong_hiding,bool multi_pole_fixed , string input_circuit_name = "none", uint circuit_lut_size = 0) {
    // Parse input into DAG
    cout << "--- Parsing Inputs ---" << endl;
    string filename = input_filename;
    if(!std::filesystem::exists(filename)){
    cout << "The file " << input_filename << " does not exist" << endl;
    exit(0);
    }
    

   

    string tmp = input_filename.substr(input_filename.length() - 6, 6);
    string circuit_name = "";
    if (tmp == ".bench") {
        cout << "Convert .bench to SHDL" << endl;
        parse_bench(input_filename, copies);
        string tmp2 = input_filename.substr(0, input_filename.length() - 6);
        string circuit_name = tmp2.substr(8, tmp2.length() - 8);
        cout << "Circuit name: " << circuit_name << endl;
        filename = "circuits/" + circuit_name + "_SHDL";
    }
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();
    std::cout << "Given circuit file: " << filename << "\n";
    DAG* gx = read_SHDL_to_Gamma(filename);
    cout << "Circuit transformed to DAG" << endl;
    

    
    if(strong_hiding)
    {
    	cout << "Strong Hiding: Transforming double wire usages into duplicate truth tables" << "\n";
    	gx->remove_double_wire_usages();
    }
	/*
    
    for(auto v: gx->vertices)
    {
    	cout << "===" << v->type << " " << v->number << "===\n";
    	for(auto in: v->in_edges)
    	{
    	cout << in->from->number << " " << in->from_slot << " " << in->to_slot << ", ";
    	}
    	cout << "->";
    	for(auto in: v->out_edges)
    	{
    	cout << in->to->number << " " << in->from_slot << " " << in->to_slot << ", ";
    	}
    	for(auto bits: v->function_bits)
    	{
    		for(auto b: bits)
    		{
    		cout << b << " ";
    		}
    		cout << "\n";
    	}
    	cout << "===========\n";
    }
    */

    gx->print_graph("DAGsimple");
    //exit(0);
    vector<uint> dag_sizes;
    cout << "Original graph stats:" << endl;
    vector<uint> dag_stats = gx->get_stats();
    dag_sizes.push_back(dag_stats[0] + dag_stats[1] + dag_stats[3]);
    uint max_orig_indegree = dag_stats[3];
    uint max_fanout = max_orig_indegree;
    if (fanout > 2 && fanout > max_orig_indegree){
        max_fanout = fanout;
    } else if (in_place)
    {
    		
            //max_fanout = max(2,fanout);
            max_fanout = (fanout>2) ? fanout : 2;
    }
    //max_fanout = 2;
    cout << "Max fanout set to " << max_fanout << endl;

    vector<pair<DAG::Node*,DAG::Node*>> outputpole_mapping;
    if(!in_place && multi_pole_fixed)
    {

/*
        for(auto v : gx->vertices)
        {

            while(v->function_bits.size()<3)
            {
                vector<int> new_func_bits;
                int arity = 1 << v->in_edges.size();
                for(int i = 0; i < arity;i++)
                {
                    new_func_bits.push_back(0);
                }
                v->function_bits.push_back(new_func_bits);
            }
        }
*/
        cout << "Adjusting description\n";
        outputpole_mapping = gx->transform_fixed_multi_pole_auxiliary_graph();
    }


    


    //  Possibly reduce fanout of DAG
    cout << "--- Possibly reducing fanout ---" << endl;
    //
     if(!in_place && multi_pole_fixed)
    {
    gx->reduce_fan_out2(max_orig_indegree);
    }
    

   // gx->print_graph("DAG");


    //exit(0);
    cout << "Fanout reduced graph stats:" << endl;
    dag_stats = gx->get_stats();
    dag_sizes.push_back(dag_stats[0] + dag_stats[1] + dag_stats[3]);

    int gate_amount[10][10];
    for(int i = 0; i < 10; i++)
    {
    	for(int j = 0; j < 10; j++)
    	{
    	gate_amount[i][j] = 0;
    	}
    }
    
    /*
    for(DAG::Node* v : gx->vertices)
    {
    	if(v->type == "gate")
    	{
    		if(v->in_edges.size() > 0)
    		gate_amount[v->in_edges.size()][v->function_bits.size()] = gate_amount[v->in_edges.size()][v->function_bits.size()] + 1;
    	}
    }
    */
    for(int i = 1; i < 10; i++)
    {
    	for(int j = 1; j < 10; j++)
    	{
    		if(gate_amount[i][j] > 0)
    		cout << i << " -> " << j << " LUTs: \t"<< gate_amount[i][j] << "\n";
    	}
    }

    unordered_map<int, int> pole_mapping;
    unordered_map<int, vector<int>> in_forwarding_poles;
    unordered_map<int, vector<int>> out_forwarding_poles;
    DAG* gx_old = gx;
    // Use dynamic multi input gates
    if (in_place) {
        cout << "--- Using in-place multi input gates ---" << endl;
        gx_old = gx;
        pair<DAG*,pair<unordered_map<int,int>,pair<unordered_map<int,vector<int>>,unordered_map<int,vector<int>>>>> transform_info = gx->transform_in_place_graph(max_fanout);
        gx = transform_info.first;
        pole_mapping = transform_info.second.first;
        in_forwarding_poles = transform_info.second.second.first;
        out_forwarding_poles = transform_info.second.second.second;
        cout << "In-place graph stats:" << endl;
        dag_stats = gx->get_stats();
    }
    
    
    //gx->print_graph("DAG_aux");
    
    
    
    dag_sizes.push_back(dag_stats[0] + dag_stats[1] + dag_stats[3]);


    uint32_t inputs = dag_stats[0];
    uint32_t gates = dag_stats[1];
    uint32_t outputs = dag_stats[2];
    


    // Split into Gamma1 graphs
    cout << "--- Splitting into Gamma1 graphs ---" << endl;
    vector<DAG*> dag1s = gx->split_into_gamma1(max_fanout);

    cout << "--- Creating Gamma1 EUGs ---" << endl;
    vector<ValiantBase*> eug1s;
    for (uint i = 0; i < dag1s.size(); i++) {
        if (algorithm == "valiant") {
            eug1s.push_back(new Valiant2Way(inputs, gates, outputs, "(" + to_string(i) + ")", true));
        }
        else if (algorithm == "liu") {
            eug1s.push_back(new Liu2Way(inputs, gates, outputs, "(" + to_string(i) + ")", true));
        }
        else {
            cerr << "Construction algorithm unknown" << "\n";
            assert(false);
        }
    }

    cout << "--- Edge embedding Gamma1 graphs ---" << endl;
    int k = 0;
    for (ValiantBase* eug1 : eug1s) {
        eug1->edge_embed_gamma1(dag1s[k]);
        eug1->remove_x_switches();
        k++;
    }

    pair<vector<ulong>,vector<ulong>> ret_pair;
    vector<ulong> eug_stats;
    vector<ulong> eug_ugs;
    
    cout << "--- Merging " << eug1s.size() <<" Gamma1 EUGs ---" << endl;
    ValiantMerged* eug = new ValiantMerged(eug1s);


    eug->set_pole_information(gx);
    eug->transform_to_ABY_format();
    eug->remove_zero_degree_vertices();

    if (correctness_check){
        bool check11 = eug->check_correctness(gx);
        assert(check11);
        std::cout << "EUG correctness check passed!" << "\n";
    }

    
    if (in_place) {
        cout << "--- Setting up multi input gates ---" << endl;
        //eug->print_graph("UnreducedUC");
        eug->prepare_k_input(gx, gx_old, pole_mapping, in_forwarding_poles);
        //eug->print_graph("ReducedUC");
        eug->prepare_k_output(gx, gx_old, pole_mapping, out_forwarding_poles);
        eug->transform_to_ABY_format();
        eug->remove_zero_degree_vertices();
        ret_pair = eug->show_stats(max_fanout, in_place);
        eug_stats = ret_pair.first;
        eug_ugs = ret_pair.second;
        if (correctness_check){
            bool check111 = eug->check_correctness(gx_old, pole_mapping);
            assert(check111);
            std::cout << "Multi input gates correctness check passed!" << "\n";
        }
    }



    int default_assignment = in_place ? 0 : eug1s.size()-1;
    if (in_place){
        eug->set_gates(gx_old,pole_mapping, default_assignment);
    } else{
        // If there is no pole mapping, set the pole mapping to be the identidy
        if (pole_mapping.size() == 0){
            for(DAG::Node* v: gx->vertices){
                pair<int,int> tmp = make_pair(v->number,v->number);
                pole_mapping.insert(tmp);
            }
        }
        eug->set_gates(gx,pole_mapping, default_assignment);
    }


    if (!in_place && multi_pole_fixed)
    {
        eug->relay_input_edges(gx,outputpole_mapping);
    }

    std::cout << "Creating Circuit files!" << endl;
    eug->print_graph("FinalUC");
    
    
    eug->create_circuit_files(in_place);
    std::cout << "Circuit files created!" << endl;
    
    if (correctness_check){
        bool circuit_check = eug->check_circuit_correctness(filename, 1);
        assert(circuit_check);
        std::cout << "Universal Circuit correctness check passed!" << endl;
    }

	if(!in_place)
	{
		int max_from_slot = 0;
    		for (ValiantMerged::Node* curr : eug->poles) {
    			if (curr->type == "gate") {
    				for(ValiantMerged::Edge* e: curr->out_edges)
    				{
    				if(e->from_slot > max_from_slot) max_from_slot = e->from_slot; 
    				}
    
    			}
    		}
    		// ASSIGN MAXIMUM
    		for (ValiantMerged::Node* curr : eug->poles) {
    			if (curr->type == "gate") {
    				for(ValiantMerged::Edge* e: curr->out_edges)
    				{
    				e->from_slot = max_from_slot; 
    				}
    			}
    		}
	}

    
    ret_pair = eug->show_stats(max_fanout, in_place);
    eug_stats = ret_pair.first;
    eug_ugs = ret_pair.second;
    
    
	auto x_gates = eug_stats[2];
	auto y_gates = eug_stats[3];
    
    
    
    // Save the size properties etc. of the UC in benchmarks.txt
    save_results("benchmarks.txt", filename, algorithm, in_place,x_gates,y_gates, max_fanout, ret_pair, dag_sizes, input_circuit_name, circuit_lut_size);


    auto t2 = high_resolution_clock::now();
    auto secs = duration_cast<milliseconds>(t2-t1);

    std::cout << secs.count() << "ms\n";
    return 0;
}

// This function builds UCs for all .bench files in "/benches" without sub directories
void benchmark(){
    namespace fs = std::filesystem;
    string path = "benches/";
    vector<string> circuits;
    vector<string> params;
    vector<pair<string,uint>> circuit_params;
    string circuit_name = "NO_NAME";
    uint circuit_lut_size = 0;
    for (const auto & entry : fs::directory_iterator(path)){
        if (entry.path().extension() == ".bench"){
            cout << entry.path() << endl;
            circuits.push_back(entry.path());
            params = parse_filename(entry.path().filename());
            circuit_name = params[0];
            circuit_lut_size = stoi(params[1]);
            circuit_params.push_back(make_pair(circuit_name, circuit_lut_size));
        }
    }
    for(uint i=0; i < circuits.size(); i++){
        create_UC(circuits[i], "liu", true,0,1, false, true,true, circuit_params[i].first, circuit_params[i].second);
    }
    for(uint i=0; i < circuits.size(); i++){
        create_UC(circuits[i], "liu", false,0,1, false, true,true, circuit_params[i].first, circuit_params[i].second);
    }
}

int main(int argc, char* argv[]) {
    //shdl_to_bench("AES-expanded.txt_SHDL.circuit");
    //shdl_to_bench("md5.txt_SHDL.circuit");
    //return 0;
    string filename;
    string algorithm = "valiant";
    int copies = 1;
    bool inplace = false;
    uint fanout = 0;
    bool correctness_check = true;
    bool strong_hiding = false;
    bool multi_pole_fixed = false;

    static const struct option long_options[] =
    {
        { "file", required_argument,0, 'f' },
        { "liu", no_argument,       0, 'l' },
        { "inplace", no_argument, 0, 'i' },
        { "mergings", required_argument,       0, 0 },
        { "copies", required_argument,       0, 0 },
        { "no_check", no_argument,       0, 'n' },
        { "strong_hiding", no_argument,       0, 's' },
        { "multi_poles", no_argument,       0, 'm' },
        0
    };
    while (1) {
        int index = -1;
        struct option* opt = 0;
        int result = getopt_long(argc, argv,
            "f:lism",
            long_options, &index);
        if (result == -1) break;
        switch (result) {
        case 's':
            cout << "Strong ULUT information hiding enabled." << "\n";
            strong_hiding = true;
            break;
        case 'f':
            cout << "Given circuit file: " << optarg << "\n";
            filename = optarg;
            break;
        case 'l':
            cout << "Liu's construction will be used." << "\n";
            algorithm = "liu";
            break;
        case 'i':
            cout << "Inplace multi input gates enabled." << "\n";
            inplace = true;
            break;
        case 'm':
            cout << "Use one pole per semantic output (Only for fixed construction)." << "\n";
            multi_pole_fixed = true;
            break;
        case 'n':
            cout << "Correctness checks disabled." << "\n";
            correctness_check = false;
            break;
        case 0:
            opt = (struct option*)&(long_options[index]);
            if (std::string(opt->name) == "mergings" && opt->has_arg == required_argument) {
                cout << "Maximum fanout of EUG set to " << optarg << ".\n";
                fanout = stoi(optarg);
            }
            else if (std::string(opt->name) == "copies" && opt->has_arg == required_argument) {
                cout << "Number of bench copies set to " << optarg << ".\n";
                copies = stoi(optarg);
            }
            break;
        default:
            break;
        }
    }
    while (optind < argc) {
        cout << "other parameter: " << argv[optind++] << "\n";
    }

    create_UC(filename, algorithm, inplace, fanout, copies, correctness_check,strong_hiding,multi_pole_fixed);
    
    return 0;
}
