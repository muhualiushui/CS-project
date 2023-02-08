#include "path_image.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#include "color.hpp"

const int kRGBr1 = 252;
const int kRGBg1 = 25;
const int kRGBb1 = 63;
const int kRGBr2 = 31;
const int kRGBg2 = 253;
const int kRGBb2 = 13;
PathImage::PathImage(const GrayscaleImage& image,
                     const ElevationDataset& dataset) {
  width_ = dataset.Width();
  height_ = dataset.Height();
  size_t best_path = 0;
  const unsigned int kCompare = 99999999;
  unsigned int compare = kCompare;
  for (size_t i = 0; i < height_; i++) {
    size_t position = i;
    Path path(dataset.Width(), position);
    path.SetLoc(0, position);  // work
    AddPath(position, dataset, path);
    if (compare > paths_[i].EleChange()) {
      compare = paths_[i].EleChange();
      best_path = i;
    }
  }

  for (size_t i = 0; i < image.Height(); i++) {
    std::vector<Color> transit;
    for (size_t j = 0; j < image.Width(); j++) {
      transit.push_back(image.GetImage()[i][j]);
    }
    path_image_.push_back(transit);
  }
  for (size_t i = 0; i < paths_.size(); i++) {
    for (size_t j = 0; j < paths_[i].GetPath().size(); j++) {
      path_image_[paths_[i].GetPath()[j]][j].ChangeColor(
          kRGBr1, kRGBg1, kRGBb1);
    }
  }
  for (size_t i = 0; i < paths_[best_path].GetPath().size(); i++) {
    path_image_[paths_[best_path].GetPath()[i]][i].ChangeColor(
        kRGBr2, kRGBg2, kRGBb2);
  }
}

const int kMaxValue = 10000;
void PathImage::AddPath(size_t& position,
                        const ElevationDataset& dataset,
                        Path& path) {
  for (size_t j = 0; j < dataset.Width() - 1; j++) {  // all path added
    size_t position2 = 0;
    int least = kMaxValue;
    if (position != 0 && position != dataset.Height() - 1) {  // immidiate
      for (int k = 0; k < 3; k++) {
        int difference = abs(dataset.DatumAt(position - 1 + k, j + 1) -
                             dataset.DatumAt(position, j));
        if (difference <= least) {
          if (k == 2 && difference == least && position2 == position) {
            break;
          }
          position2 = position - 1 + k;
          least = difference;
        }
      }
    } else {  // top and bottem
      for (int k = 0; k < 2; k++) {
        size_t change = position - 1;
        if (position == 0) {
          change++;
        }
        int difference = abs(dataset.DatumAt(change + k, j + 1) -
                             dataset.DatumAt(position, j));
        if (difference <= least) {
          if (k == 1 && difference == least && position2 == position) {
            break;
          }
          position2 = change + k;
          least = difference;
        }
      }
    }
    path.SetLoc(j + 1, position2);
    path.IncEleChange(least);
    position = position2;
  }
  paths_.push_back(path);
}

size_t PathImage::Width() const { return width_; }
size_t PathImage::Height() const { return height_; }
unsigned int PathImage::MaxColorValue() const { return kMaxColorValue; }
const std::vector<Path>& PathImage::Paths() const { return paths_; }
const std::vector<std::vector<Color>>& PathImage::GetPathImage() const {
  return path_image_;
}
void PathImage::ToPpm(const std::string& name) const {
  std::ofstream ofs(name);
  ofs << "P3" << '\n';
  ofs << Width() << " " << Height() << '\n';
  ofs << kMaxColorValue << '\n';
  for (size_t i = 0; i < path_image_.size(); i++) {
    for (const auto& color : path_image_[i]) {
      ofs << color;
    }
    ofs << '\n';
  }
}