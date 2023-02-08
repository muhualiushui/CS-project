#include "grayscale_image.hpp"

#include <cmath>
#include <cstdlib>  // for size_t
#include <fstream>
#include <iostream>
#include <vector>

GrayscaleImage::GrayscaleImage(const std::string& filename,
                               size_t width,
                               size_t height) {
  ElevationDataset elevate(filename, width, height);
  const int kMax = 255;
  for (size_t i = 0; i < elevate.GetData().size(); i++) {
    std::vector<Color> transit = {};
    for (size_t j = 0; j < elevate.GetData()[i].size(); j++) {
      double color = 0;
      if (elevate.MaxEle() ==
          elevate.MinEle()) {  // wehther max and min is equal
        color = 0;
      } else {
        color = std::round(
            (double)((elevate.GetData()[i][j] - elevate.MinEle()) * kMax) /
            (double)(elevate.MaxEle() -
                     elevate.MinEle()));  // calculate the color
      }
      std::cout << color << std::endl;
      Color c((int)color, (int)color, (int)color);
      transit.push_back(c);
    }
    image_.push_back(transit);
  }
  width_ = elevate.Width();
  height_ = elevate.Height();
}

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
  const int kMax = 255;
  for (size_t i = 0; i < dataset.GetData().size(); i++) {
    std::vector<Color> transit = {};
    for (size_t j = 0; j < dataset.GetData()[i].size(); j++) {
      double color = 0;
      if (dataset.MaxEle() ==
          dataset.MinEle()) {  // wehther max and min is equal
        color = 0;

      } else {
        color = std::round(
            (double)((dataset.GetData()[i][j] - dataset.MinEle()) * kMax) /
            (double)(dataset.MaxEle() -
                     dataset.MinEle()));  // calculate the color
      }

      Color c((int)color, (int)color, (int)color);
      transit.push_back(c);
    }
    image_.push_back(transit);
  }
  width_ = dataset.Width();
  height_ = dataset.Height();
}

size_t GrayscaleImage::Width() const { return width_; }
size_t GrayscaleImage::Height() const { return height_; }
unsigned int GrayscaleImage::MaxColorValue() const { return kMaxColorValue; }
const Color& GrayscaleImage::ColorAt(int row, int col) const {
  return image_[row][col];
}
const std::vector<std::vector<Color>>& GrayscaleImage::GetImage() const {
  return image_;
}
void GrayscaleImage::ToPpm(const std::string& name) const {
  std::ofstream ofs(name);
  ofs << "P3" << '\n';
  ofs << Width() << " " << Height() << '\n';
  ofs << kMaxColorValue << '\n';
  for (size_t i = 0; i < image_.size(); i++) {
    for (const auto& color : image_[i]) {
      ofs << color;
    }
    ofs << '\n';
  }
}

std::ostream& operator<<(std::ostream& os, const Color& c) {
  os << c.Red() << " " << c.Green() << " " << c.Blue() << " ";
  return os;
}