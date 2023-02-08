#include <iostream>

#include "branched-linked-list.hpp"

int main() {
  /* EXAMPLE INTERACTIONS WITH BLL */
  BLL* first = new BLL();
  first->PushBack('a');
  first->PushBack('a');
  first->PushBack('a');

  std::cout << first->ToString() << std::endl;  // hi
  std::cout << first->Size() << std::endl;      // 2

  // /////////////////////////////////////

  BLL* second = new BLL();
  second->PushBack('b');
  second->PushBack('b');
  second->PushBack('b');

  std::cout << second->ToString() << std::endl;  // i!@
  std::cout << second->Size() << std::endl;      // 3

  // /////////////////////////////////////

  first->Join(1, second);

  std::cout << first->ToString() << std::endl;  // hii!@
  std::cout << first->Size() << std::endl;      // 5

  BLL* third = new BLL();
  third->PushBack('c');
  third->PushBack('c');
  third->PushBack('c');

  std::cout << third->ToString() << std::endl;  // i!@
  std::cout << third->Size() << std::endl;      // 3

  first->Join(first->Size() - 1, second);

  std::cout << first->ToString() << std::endl;  // hii!@
  std::cout << first->Size() << std::endl;      // 5

  // third->Join(2, second);

  // std::cout << first->ToString() << std::endl;  // hii!@
  // std::cout << first->Size() << std::endl;      // 5
  // first->Join(2, second);

  // std::cout << first->ToString() << std::endl;  // hii!@
  // std::cout << first->Size() << std::endl;      // 5

  // first->Join(4, first);
  // std::cout << first->GetAt(4) << std::endl;
  // first->SetAt(4, 'L');
  // std::cout << first->GetAt(4) << std::endl;
  // std::cout << second->ToString() << std::endl;  // i!@
  // std::cout << second->Size() << std::endl;      // 3

  // // /////////////////////////////////////

  // BLL* first_clone = new BLL();
  // *first_clone = *first;

  // std::cout << first_clone->ToString() << std::endl;  // hii!@
  // std::cout << first_clone->Size() << std::endl;      // 5

  return 0;
}
