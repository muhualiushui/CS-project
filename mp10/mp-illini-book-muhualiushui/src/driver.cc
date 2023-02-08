#include <iostream>

#include "illini_book.hpp"
int main() {
  IlliniBook start("./example/persons.csv", "./example/relations.csv");
  // int uin_1 = 1;
  // int uin_2 = 2;
  // std::string relationship = "";
  // if (start.AreRelated(uin_1, uin_2)) {
  //   std::cout << "have path" << std::endl;
  //   std::cout << start.GetRelated(uin_1, uin_2, relationship) << std::endl;
  // } else {
  //   std::cout << "no result" << std::endl;
  //   std::cout << start.GetRelated(uin_1, uin_2, relationship) << std::endl;
  // }
  for (auto single : start.GetSteps(6, 2)) {
    std::cout << single << std::endl;
  }
  // std::cout << start.CountGroups() << std::endl;
  // std::cout << start.CountGroups("124") << std::endl;
  // std::cout << start.CountGroups(std::vector<std::string>{"128", "124"})
  //           << std::endl;
  return 0;
}
