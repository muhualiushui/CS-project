#include <fstream>
#include <iostream>
#include "functions.hpp"
#include "utilities.hpp"
int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " [input_file] [dna_sequence]"
              << std::endl;
    return 1;
  }
  std::ifstream ifs{argv[1]};

  std::vector<std::vector<std::string>> database;  // add database into memory
  for (std::string line; std::getline(ifs, line); line = "") {
    database.push_back(utilities::GetSubstrs(line, ','));

  }
  const std::string& dna = argv[2];
  std::vector<int> input_dna;
  for (size_t i = 1; i < database[0].size(); i++) {
    input_dna.push_back(
        NumberOfSequenceOfAGATG(dna, database[0][i], database[0][i].size()));
  }

  for (size_t i = 0; i < input_dna.size(); i++) {
  }
  std::string answer;
  answer = Match(database, input_dna);
  std::cout << answer << std::endl;
  return 0;
}