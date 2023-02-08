#include "functions.hpp"
#include <iostream>
int NumberOfSequenceOfAGATG(const std::string& dna,
                            const std::string& detect,
                            const int& number) {
  int count = 0;
  int max_long = 0;
  for (size_t i = 0; i < dna.size() - number + 1; i++) {
    if (dna.substr(i, number) == detect) {
      i += number - 1;
      count++;
    } else {
      if (count > max_long) {
        max_long = count;
      }
      count = 0;
    }
  }
  if (count > max_long) {
    max_long = count;
  }
  return max_long;
}
std::string Match(std::vector<std::vector<std::string>> database,
                  std::vector<int> input_dna) {
  bool match = false;
  int name_at = 0;
  for (size_t i = 1; i < database.size(); i++) {
    int count = 0;
    for (size_t j = 0; j < input_dna.size(); j++) {
      int number_as_int = std::stoi(database[i][j + 1]);
      if (input_dna[j] == number_as_int) {
        count++;
      }
    }
    if (count == 3) {
      name_at = i;
      match = true;
      break;
    }
  }
  if (match) {
    return database[name_at][0];
  }
  return "No Match";
}