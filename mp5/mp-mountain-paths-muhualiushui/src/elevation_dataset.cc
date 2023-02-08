#include "elevation_dataset.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

ElevationDataset::ElevationDataset(const std::string& filename,
                                   size_t width,
                                   size_t height) {
  std::ifstream ifs{filename};
  int value = 0;
  size_t count = 0;
  size_t w = 0;
  if (!ifs.is_open()) {
    throw std::runtime_error("can not open file");
  }
  std::vector<int> transition;
  while (ifs >> value) {  // add database into memory
    transition.push_back(value);
    w++;
    if (w == width) {
      data_.push_back(transition);
      transition.erase(transition.begin(),
                       transition.begin() + transition.size());
      w = 0;
    }
  }
  if (w != 0 || data_.size() != height) {
    throw std::runtime_error("invalid input");
  }
  max_ele_ = data_[0][0];
  min_ele_ = data_[0][0];
  for (size_t i = 0; i < data_.size(); i++) {  // count number of total integers
    for (size_t j = 0; j < data_[i].size(); j++) {  // classify max and min
      if (data_[i][j] > max_ele_) {
        max_ele_ = data_[i][j];
      }
      if (data_[i][j] < min_ele_) {
        min_ele_ = data_[i][j];
      }
      count++;
    }
  }
  if (width * height != count) {
    throw std::runtime_error("invalid width or height");
  }
  width_ = width;
  height_ = height;
}

// bool has_value = false;
// for (size_t i = 0; i < line.length(); i++) {
//   if (line.at(i) > '0' && line.at(i) < '9') {
//     has_value = true;
//     break;
//   }
// }
// if (has_value) {
//   data_.push_back(GetSubstrs(line, ' '));
// }

// std::vector<int> GetSubstrs(const std::string& str,
//                             char delimiter) {  // subtract every int
//   std::vector<int> substrs;
//   std::string substr;

//   for (size_t i = 0; i < str.length(); i++) {
//     int count = 0;
//     if (str.at(i) == delimiter && !substr.empty()) {
//       for (size_t i = 0; i < substr.length(); i++) {
//         if (substr.at(i) < '0' || substr.at(i) > '9') {
//           if (substr.at(i) != '-') {
//             throw std::runtime_error("invalid input");
//           }
//         }
//       }
//       for (size_t i = 0; i < substr.length(); i++) {
//         if (substr.at(i) >= '0' && substr.at(i) <= '9') {
//           count++;
//         }
//       }
//       if (count > 0) {
//         substrs.push_back(std::stoi(substr));
//       }
//       substr = "";
//     } else {
//       if ((str.at(i) >= '0' && str.at(i) <= '9') || str.at(i) == '-') {
//         substr += str.at(i);
//       }
//     }
//   }
//   substrs.push_back(stoi(substr));
//   return substrs;
// }

size_t ElevationDataset::Width() const { return width_; }
size_t ElevationDataset::Height() const { return height_; }
int ElevationDataset::MaxEle() const { return max_ele_; }
int ElevationDataset::MinEle() const { return min_ele_; }
int ElevationDataset::DatumAt(size_t row, size_t col) const {
  return data_[row][col];
}
const std::vector<std::vector<int>>& ElevationDataset::GetData() const {
  return data_;
}