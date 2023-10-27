#include <unordered_map>
#include "utility.h"
#include <unordered_map>

void tokenize(const string& str, vector<string>& tokens) {
	tokens.clear();
    char delimiter = ' ';
	string::size_type last_pos = str.find_first_not_of(delimiter, 0);
	string::size_type pos = str.find_first_of(delimiter, last_pos);
	while (string::npos != pos || string::npos != last_pos) {
		tokens.push_back(str.substr(last_pos, pos - last_pos).c_str());
		last_pos = str.find_first_not_of(delimiter, pos);
		pos = str.find_first_of(delimiter, last_pos);
	}
}

vector<int> convert_hex_to_binary(int arity, string hex_str){
    stringstream ss;
    ss << hex << hex_str;
    uint64_t n;
    ss >> n;
    //cout << "input: " << hex_str << "\n";
    //cout << "decimal: " << n << "\n";
    vector<int> binary_rep = get_binary(arity, n);
    return binary_rep;
    
}


vector<int> get_binary(int arity, uint64_t num){
    vector<int> binary_rep;
    while(num > 0){
        if(num % 2 == 0){
            binary_rep.push_back(0);
        }else{
            binary_rep.push_back(1);
        }
        num >>= 1;
    }
    // Pad to needed size
    int start = binary_rep.size();
    for(int i=start; i < arity; i++){
      binary_rep.push_back(0);
    }
    reverse(binary_rep.begin(), binary_rep.end());
    return binary_rep;
}

void eval_SHDL(string filename, vector<bool>& input_list, vector<bool>& output_list){
    ifstream file;
    file.open(filename);
    unordered_map <int,bool> wire_results;
    int i = 0;
    for(bool bit: input_list){
        wire_results[i] = bit;
        i++;
    }
 
 cout << "---Evaluating original SHDL---\n";
 
 cout << "Input: ";
    for(int i = 0; i < input_list.size();i++)
    {
    cout << input_list[i];
    cout << " ";
    }
    cout << "\n";
 
    string line;
    vector<string> tokens;
	int gate_count = 0;
    while (getline(file, line)) {
        if (line != "") {
            
            tokenize(line, tokens);
            int t = 0;
            
            vector<int> edge_nums;
            while(t < tokens.size())
            {
            string token = tokens[t];
            if(token == "gate" || token == "output" || token == "input" || token == "outputs")
            {
            break;
            }
            edge_nums.push_back(stoi(token));
            t++;
            }
            
            int shift = 0;
            if(tokens[1] == "output"){
                shift = 1;
            }
            if(tokens[edge_nums.size() + shift] == "gate"){
                vector<vector<int>> function_bits;
                auto ar = tokens[edge_nums.size()+2+shift];
                
                uint arity = stoi(ar);
                uint start_index = edge_nums.size() + 5 + shift;
                int lines = pow(2,arity);
                for(int i = 0; i < edge_nums.size();i++)
                {
                vector<int> bits;
                for(int j = 0; j < lines; j++){
                    int ind =   i*(lines + 2) + j + start_index;
                    bits.push_back(stoi(tokens[ind]));
                }
                function_bits.push_back(bits);
                }
                
                vector<int> inputs;
                start_index = tokens.size() - arity - 1;
                int end_index = tokens.size() - 2;
                for(uint i=start_index; i <= end_index;i++){
                    inputs.push_back(stoi(tokens[i]));
                }
                assert(inputs.size() == arity);
                
                uint64_t pol_result = 0;
                for(uint i = 0; i < inputs.size(); i++){
                    pol_result += pow(2,arity - 1 - i) * wire_results[inputs[i]];
                }
                gate_count++;
                for(int i = 0; i < edge_nums.size();i++)
                {
                	int r = function_bits[i][pol_result];
                	wire_results [edge_nums[i]] = r;
                }
            }
            if(tokens[0] == "outputs"){
                for(uint j = 1; j < tokens.size(); ++j){
                	int t = stoi(tokens[j]);
                    output_list.push_back(wire_results[t]);
                }
            }
        }
    }
    
    cout << "Output: ";
    for(int i = 0; i < output_list.size();i++)
    {
    cout << output_list[i];
    cout << " ";
    }
    cout << "\n";
    
 cout << "---Finished evaluating original SHDL---\n";
    file.close();
}

void eval_UC(vector<bool>& input_list, vector<bool>& output_list){
    string circuit = "outputs/circuit";
    string program = "outputs/programming";

    ifstream c_file;
	c_file.open (circuit);
    ifstream p_file;
	p_file.open (program);

    vector <bool> wire_results;


    string c_line;
    string p_line;
    vector<string> c_tokens;
    vector<string> p_tokens;
    uint c_line_counter = 0;
    uint p_line_counter = 0;
    
    cout << "---Evaluating Universal Circuit---\n";

    cout << "Inputs:";
    for(auto i:input_list)
    {
    cout << " ";
    cout << i;
    }
    cout <<  "\n --- \n";

    int gate_count = 0;
    while(getline(c_file,c_line)){
        c_line_counter++;
        if (c_line == ""){
            continue;
        }
        tokenize(c_line,c_tokens);
        if (c_tokens[0] == "C"){ // Parse the input list
            assert(input_list.size() == c_tokens.size() - 1);
            for (uint i=0; i < input_list.size(); i++){
                wire_results.push_back(input_list[i]);
            }
            continue;
        } else if (c_tokens[0] == "X" || c_tokens[0] == "Y"){
            bool in1 = wire_results[stoi(c_tokens[1])];
            bool in2 = wire_results[stoi(c_tokens[2])];
            getline(p_file,p_line);
            p_line_counter++;
            tokenize(p_line, p_tokens);
            assert(p_tokens.size() == 1);
            bool control_bit = (bool) stoi(p_tokens[0]);
            if (c_tokens[0] == "X"){
                assert(c_tokens.size() == 5);
                bool out1 = (control_bit) ? in2 : in1;
                bool out2 = (control_bit) ? in1 : in2;
                wire_results.push_back(out1);
                wire_results.push_back(out2);
            } else{
                assert(c_tokens.size() == 4);
                bool out1 = (control_bit) ? in1 : in2;
                wire_results.push_back(out1);
            }
            continue;
        } else if (c_tokens[0] == "U"){
            vector<bool> gate_inputs;
            int i = 1;
            bool ins = true;
            int outputs = 0;
            gate_count++;
            while (i < c_tokens.size()){
            	if(c_tokens[i] == "|")
            	{
            	ins = false;
            	i++;
            	}
            	if(ins)
            	{
                gate_inputs.push_back(wire_results[stoi(c_tokens[i])]);
                }else
                {
                outputs++;
                }
                i++;
            }
            getline(p_file,p_line);
            p_line_counter++;
            tokenize(p_line,p_tokens);
            vector<vector<int>> programming_bits;
            
            int bits_per_line = pow(2, gate_inputs.size());

            for(int i = 0;i < outputs;i++)
            {
            	vector<int> bits;
            	for(int j = 0;j<bits_per_line;j++)
            	{
            	int id = j + (i*(bits_per_line+1));
            	string token = p_tokens[id];
            	bits.push_back(stoi(token));
            	}
            	programming_bits.push_back(bits);
            }
            
            
            //assert(p_tokens.size() == pow(2,gate_inputs.size()));
            uint64_t pol_result = 0;
            for(uint i = 0; i < gate_inputs.size(); i++){
                pol_result += pow(2,gate_inputs.size() - 1 - i) * gate_inputs[i];
            }
            assert((pol_result <= p_tokens.size() - 1) && pol_result >= 0);
            for(int j = 0; j < outputs;j++)
            {
            int result = (programming_bits[j][pol_result]);
            
            assert(result == 0 || result == 1);
            wire_results.push_back(result);
            }
            continue;
        } else if (c_tokens[0] == "O"){
            for (uint i=1; i < c_tokens.size(); i++){
                output_list.push_back(wire_results[stoi(c_tokens[i])]);
            }
            continue;
        } else{
            cout << "Unknown line format" << endl;
        }
    }


	cout << "Output: ";
	for(auto o: output_list)
	{
	cout << o;
	cout << " ";
	}
	cout << "\n";
	cout << wire_results[17] << " " << wire_results[12] << " " << wire_results[7] << "\n";
	
	cout << wire_results[18] << " " << wire_results[19] << " " << wire_results[20] << "\n";
	
 	cout << "---Finished evaluating UC---\n";
	c_file.close();
	p_file.close();
}

vector<bool> initialize_inputs(string filename){
    const char* filen = filename.c_str();
    ifstream file;
    file.open(filen);

    bool bit;
    string line;
    vector<string> tokens;
    vector<bool> input_list;

    while (getline(file, line)) {
        if (line != "") {
            tokenize(line, tokens);
            if(tokens[1] == "input"){
                bit = (0 == (rand() % 2));
                input_list.push_back(bit);                    
            }
        }
    }
    file.close();
    return input_list;
}
