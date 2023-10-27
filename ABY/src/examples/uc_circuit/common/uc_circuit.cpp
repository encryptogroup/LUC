/**
 \file 		uc_gate_test.cpp
 \author	kiss@encrypto.cs.tu-darmstadt.de
 \copyright	ABY - A Framework for Efficient Mixed-protocol Secure Two-party
 Computation Copyright (C) 2019 Engineering Cryptographic Protocols Group, TU
 Darmstadt This program is free software: you can redistribute it and/or modify
            it under the terms of the GNU Lesser General Public License as
 published by the Free Software Foundation, either version 3 of the License, or
            (at your option) any later version.
            ABY is distributed in the hope that it will be useful,
            but WITHOUT ANY WARRANTY; without even the implied warranty of
            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
            GNU Lesser General Public License for more details.
            You should have received a copy of the GNU Lesser General Public
 License along with this program. If not, see <http://www.gnu.org/licenses/>.
 \brief		Test the universal circuit evaluation
 */

#include "uc_circuit.h"

/**
 * Plain evaluation of universal circuit to check correctness
 * @param filename name of file with UC
 * @param input_list specified input bits
 * @param output_list resulting output bits
 */
void eval_UC(std::string circuit, std::string program,
             std::vector<bool> &input_list, std::vector<bool> &output_list) {
  std::ifstream file;
  file.open(circuit);
  std::ifstream file_xy;
  file_xy.open(program);

  std::map<uint32_t, bool> wires_carry;

  std::string line;
  std::string line_xy;
  std::vector<uint32_t> tokens;
  std::vector<uint32_t> tokens_xy;

  if (file.is_open()) {
    while (getline(file, line)) {
      if (line != "") {
        tokenize(line, tokens);
        /* Count the number of inputs and initialize a random bool list of
         * inputs */
        if (line.at(0) == 'C') {
          for (uint32_t j = 1; j < tokens.size(); ++j) {
            wires_carry[tokens[j]] = input_list[j - 1];
          }
        }
        if (line.at(0) == '0') {
          wires_carry[tokens[1]] = 0;
        }
        if (line.at(0) == '1') {
          wires_carry[tokens[1]] = 1;
        }
        if (line.at(0) == 'X') {
          getline(file_xy, line_xy);
          if (line_xy.at(0) == '0') {
            wires_carry[tokens[3]] = wires_carry[tokens[1]];
            wires_carry[tokens[4]] = wires_carry[tokens[2]];
          } else if (line_xy.at(0) == '1') {
            wires_carry[tokens[3]] = wires_carry[tokens[2]];
            wires_carry[tokens[4]] = wires_carry[tokens[1]];
          }
#ifdef CIRCUIT_DEBUG
          std::cout << "X " << wires_carry[tokens[1]] << " "
                    << wires_carry[tokens[2]] << std::endl;
#endif // CIRCUIT_DEBUG
        }
        if (line.at(0) == 'Y') {
          getline(file_xy, line_xy);
          if (line_xy.at(0) == '0') {
            wires_carry[tokens[3]] = wires_carry[tokens[2]];
          } else if (line_xy.at(0) == '1') {
            wires_carry[tokens[3]] = wires_carry[tokens[1]];
          }
#ifdef CIRCUIT_DEBUG
          std::cout << "Y " << wires_carry[tokens[1]] << " "
                    << wires_carry[tokens[2]] << std::endl;
#endif // CIRCUIT_DEBUG
        }
        if (line.at(0) == 'E') {
          wires_carry[tokens[3]] =
              wires_carry[tokens[1]] ^ wires_carry[tokens[2]];
#ifdef CIRCUIT_DEBUG
          std::cout << "E " << wires_carry[tokens[1]] << " "
                    << wires_carry[tokens[2]] << std::endl;
#endif // CIRCUIT_DEBUG
        }
        if (line.at(0) == 'A') {
          wires_carry[tokens[3]] =
              wires_carry[tokens[1]] && wires_carry[tokens[2]];
#ifdef CIRCUIT_DEBUG
          std::cout << "A " << wires_carry[tokens[1]] << " "
                    << wires_carry[tokens[2]] << std::endl;
#endif // CIRCUIT_DEBUG
        }
        if (line.at(0) == 'I') {
          wires_carry[tokens[2]] = !wires_carry[tokens[1]];
#ifdef CIRCUIT_DEBUG
          std::cout << "I " << wires_carry[tokens[1]] << std::endl;
#endif // CIRCUIT_DEBUG
        }
        if (line.at(0) == 'U') {
          getline(file_xy, line_xy);
          tokenize(line_xy, tokens_xy);

          assert(tokens_xy.size() == 1 << (tokens.size() - 2));

          size_t lut_index = 0;
          for (size_t j = 1; j < tokens.size() - 1; j++) {
            lut_index |= wires_carry[tokens[j]] << (tokens.size() - 2 - j);
          }
          bool temp = tokens_xy[lut_index];

          wires_carry[tokens[tokens.size() - 1]] = temp;
#ifdef CIRCUIT_DEBUG
          std::cout << "U " << wires_carry[tokens[1]] << " "
                    << wires_carry[tokens[2]] << "\t" << temp << std::endl;
#endif // CIRCUIT_DEBUG
        }
        if (line.at(0) == 'O') {
          for (uint32_t j = 1; j < tokens.size(); ++j) {
            output_list.push_back(wires_carry[tokens[j]]);
          }
        }
      }
    }
  }

  file.close();
  file_xy.close();
}

int32_t test_universal_circuit(e_role role, char *address, uint16_t port,
                               seclvl seclvl, uint32_t nvals, uint32_t bitlen,
                               uint32_t nthreads, e_mt_gen_alg mt_alg,
                               e_sharing sharing, const std::string filename,
                               const std::string p1filename, const std::string p2input) {
  std::cout << "Evaluating Universal circuit in " << get_sharing_name(sharing)
            << " Sharing" << std::endl;
  /* NO CHANGE ----------------------------------------------------*/
  /**
   Step 1: Create the ABYParty object which defines the basis of all the
   operations which are happening.	Operations performed are on the
   basis of the role played by this object.
   */
  ABYParty *party =
      new ABYParty(role, address, port, seclvl, bitlen, nthreads, mt_alg);

  /* NO CHANGE ----------------------------------------------------*/
  /**
   Step 2: Get to know all the sharing types available in the program.
   */
  std::vector<Sharing *> &sharings = party->GetSharings();

  /* NO CHANGE ----------------------------------------------------*/
  /**
   Step 3: Create the circuit object on the basis of the sharing type
   being inputed.
   */
  BooleanCircuit *circ =
      (BooleanCircuit *)sharings[sharing]->GetCircuitBuildRoutine();

  assert(circ->GetCircuitType() == C_BOOLEAN);

  srand(time(NULL));

  /* NO CHANGE ----------------------------------------------------*/
  /**
   Step 4: Creating the share objects - s_x_vec, s_y_vec which
   are used as inputs to the computation. Also, s_out which stores the output.
   */

  /* xvals should be size of the file p1filename */
  /**
   Step 5: Allocate the xvals and yvals that will hold the plaintext values.
   */
  uint32_t client_input_bits, server_input_bits;
  circ->GetInputLengthFromFile(filename, client_input_bits, server_input_bits);
  // server_input_bits = circ->GetServerInputLengthFromFile(p1filename);
  // uint32_t client_input_bits = circ->GetClientInputLengthFromFile(filename);
  // std::cout << "Server input bits = " << server_input_bits << ", client input
  // bits = " << client_input_bits << std::endl;

  /**
   Step 6: Fill the arrays xvals and yvals with the generated random values.
   Both parties use the same seed, to be able to verify the
   result. In a real example each party would only supply
   one input value. Copy the randomly generated std::vector values into the
   respective share objects using the circuit object method PutINGate(). Also
   mention who is sharing the object. The values for the party different from
   role is ignored, but PutINGate() must always be called for both roles.
   */

  std::vector<uint32_t> p2inputs, results, outputs;
  std::vector<bool> verif_p2inputs, verif_results;
  struct timespec cstart, cend;
  clock_gettime(CLOCK_MONOTONIC, &cstart);

  uint32_t temp;

  for (uint32_t j = 0; j < client_input_bits; ++j) {
    if (j < p2input.size()) {
      assert(p2input[j] == '0' || p2input[j] == '1');
      temp = (p2input[j] == '0') ? 0 : 1;
    } else {
      temp = 0;
    }

    verif_p2inputs.push_back(temp);
    p2inputs.push_back(circ->PutSIMDINGate(nvals, temp, CLIENT));
  }
  std::cout << std::endl << "INPUTS: ";
  for (uint32_t j = 0; j < client_input_bits; ++j) {
    std::cout << verif_p2inputs[j];
  }
  std::cout << std::endl;
  // std::cout << "PutInGate for CLIENT done" << std::endl;

  /**
       Step 7: Call the build method for building the circuit for the
       problem by passing the shared objects and circuit object.
       Don"t forget to type cast the circuit object to type of share
       */
  results =
      circ->PutUniversalCircuitFromFile(filename, p1filename, p2inputs, nvals);

  /**
    Step 8: Output the value of s_out (the computation result) to both parties
  */
  for (uint32_t i = 0; i < results.size(); i++) {
    outputs.push_back(circ->PutOUTGate(results[i], ALL));
  }

  clock_gettime(CLOCK_MONOTONIC, &cend);
  std::cout << "BuildTime = \t" << getMillies(cstart, cend) << " ms"
            << std::endl;

  /**
   Step 9: Executing the circuit using the ABYParty object evaluate the
   problem.
   */
  party->ExecCircuit();

  uint32_t val = 0;
  std::cout << std::endl << "OUTPUTS: ";
  for (uint32_t i = 0; i < outputs.size(); i++) {
    val = circ->GetOutputGateValue(outputs[i])[0];
    std::cout << val;
  }
  std::cout << std::endl;

  /**
   Step 10: Type caste the plaintext output to 16 bit unsigned integer.
   */

  std::ofstream file;
  std::cout << "Total time / comm: " << party->GetTiming(P_TOTAL) << " ms / "
            << party->GetSentData(P_TOTAL) + party->GetReceivedData(P_TOTAL)
   
            << " bytes " << std::endl;



    std::ofstream file_out;
    std::ifstream infile("benchmarks.txt");
    bool exists = infile.good();
    file_out.open("benchmarks.txt", std::ios_base::app);
    if(!exists)
    {
    	file_out << "name"<<"\t"<<"role"<<"\t"<<"sharing" << "\t" << "time" << "\t" << "data"<< "\t"<< "multiout" << std::endl;
    }
    file_out << filename <<"\t" << role << "\t" << sharing  << "\t" << party->GetTiming(P_TOTAL) << "\t" << party->GetSentData(P_TOTAL) + party->GetReceivedData(P_TOTAL) <<"\t"<< "0"<< std::endl;
    file_out.close();
    
    
  eval_UC(filename, p1filename, verif_p2inputs, verif_results);
  for (uint32_t i = 0; i < verif_results.size(); ++i) {
    std::cout << verif_results[i];
  }
  std::cout << std::endl;

  file.close();
  delete party;

  return 0;
}
