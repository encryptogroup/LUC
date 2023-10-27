#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

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
#include <bitset>
#include <cassert>
#include <math.h>
#include <cstdlib>

using namespace std;

void tokenize(const std::string& str, std::vector<string>& tokens);
void eval_SHDL(string filename, vector<bool>& input_list, vector<bool>& output_list);
void eval_UC(vector<bool>& input_list, vector<bool>& output_list);
vector<bool> initialize_inputs(string filename);
vector<int> convert_hex_to_binary(int arity, string hex_str);
vector<int> get_binary(int arity, uint64_t num);
template <class T>
int find_index(vector<T> &vec, T elem);
template <class T>
int find_index(vector<T> &vec, T elem){
    for(uint i=0; i<vec.size(); i++){
        if (vec[i] == elem){
            return i;
        }
    }
    return -1;
}


#endif // UTILITY_H_INCLUDED