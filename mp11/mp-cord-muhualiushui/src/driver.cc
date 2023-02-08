#include <cassert>
#include <iostream>

#include "cord-utilities.hpp"
#include "cord.hpp"

int main() {
  shared_ptr<Cord> c7 = make_shared<Cord>("!!!");
  shared_ptr<Cord> c6 = make_shared<Cord>("fucker");
  shared_ptr<Cord> c5 = make_shared<Cord>("mother");
  shared_ptr<Cord> c4 = make_shared<Cord>("hello");
  shared_ptr<Cord> c3 = make_shared<Cord>(c6, c7);
  shared_ptr<Cord> c2 = make_shared<Cord>(c4, c5);
  shared_ptr<Cord> c1 = make_shared<Cord>(c2, c3);
  // shared_ptr<Cord> new_c = c1->SubString(4, 14);
  std::cout << c1-> << std::endl;
}
