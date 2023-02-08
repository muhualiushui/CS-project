#include "cord-utilities.hpp"

std::shared_ptr<Cord> ConcatCords(std::shared_ptr<Cord> left_cord,
                                  std::shared_ptr<Cord> right_cord) {
  if (!left_cord->IsValidCord() || !right_cord->IsValidCord()) {
    throw std::runtime_error("is not valid card");
  }
  shared_ptr<Cord> c1 = make_shared<Cord>(left_cord, right_cord);
  return c1;
}

void ReduceCords(cs128::ReferenceList<std::shared_ptr<Cord>> cords) {
  cords={};
}
