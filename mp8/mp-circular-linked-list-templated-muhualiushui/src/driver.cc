#include <iostream>

#include "circular-linked-list.hpp"

int main() {
  CircularLinkedList<int> cll;
  cll.InsertInOrder(12);
  // cll.InsertInOrder(10);
  // cll.InsertInOrder(13);
  // cll.InsertInOrder(11);
  // cll.InsertInOrder(14);
  std::cout << cll << std::endl;
  cll.Reverse();
  std::cout << cll << std::endl;
}
