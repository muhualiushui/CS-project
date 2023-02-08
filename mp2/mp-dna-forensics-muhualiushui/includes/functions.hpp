#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "utilities.hpp"
int NumberOfSequenceOfAGATG(const std::string& dna,
                            const std::string& detect,
                            const int& number);
std::string Match(std::vector<std::vector<std::string>> database,
                  std::vector<int> input_dna);
#endif