#include "path.hpp"

#include <iostream>

#include "elevation_dataset.hpp"

Path::Path(size_t length, size_t starting_row) {
  starting_row_ = starting_row;
  length_ = length;
  for (size_t i = 0; i < length; i++) {
    path_.push_back(0);
  }
}
size_t Path::Length() const { return length_; }
size_t Path::StartingRow() const { return starting_row_; }
unsigned int Path::EleChange() const { return ele_change_; }
void Path::IncEleChange(unsigned int value) { ele_change_ += value; }
const std::vector<size_t>& Path::GetPath() const { return path_; }
void Path::SetLoc(size_t col, size_t row) { path_.at(col) = row; }
