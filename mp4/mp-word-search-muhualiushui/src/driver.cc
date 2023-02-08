#include <iostream>
#include <string>
#include <vector>

#include "WordSearchSolver.hpp"

int main() {
  std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                        {'h', 'e', 'l', 'l', 'o'},
                                        {'c', 'a', 'l', 'o', 'm'},
                                        {'a', 'e', 't', 'a', 'u'},
                                        {'t', 'e', 't', 'o', 'u'}};
  WordSearchSolver wss(puzzle);
  // std::cout << wss.FindWord("hello", CheckDirection::kHorizontal);
  std::cout << wss.FindWord("lltt", CheckDirection::kVertical);
  std::cout << wss.FindWord("muu", CheckDirection::kVertical);
  std::cout << wss.FindWord("oao", CheckDirection::kVertical);
  std::cout << wss.FindWord("dhc", CheckDirection::kVertical);
  std::cout << wss.FindWord("eeae", CheckDirection::kVertical);
  std::cout << wss.FindWord("ol", CheckDirection::kVertical);
  std::cout << wss.FindWord("aee", CheckDirection::kVertical);
  std::cout << wss.FindWord("hcat", CheckDirection::kVertical);
  std::cout << wss.FindWord("eeaee", CheckDirection::kVertical);
  std::cout << wss.FindWord("uuu", CheckDirection::kVertical);
  // std::cout << wss.FindWord("delau", CheckDirection::kRightDiag);
  // std::cout << wss.FindWord("mat", CheckDirection::kLeftDiag);
}