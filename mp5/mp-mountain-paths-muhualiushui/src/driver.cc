#include <iostream>
#include <string>

#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path_image.hpp"
int main() {
  ElevationDataset e(
      "./example-data/ex_input_data/map-input-w51-h55.dat", 51, 55);
  GrayscaleImage g(e);
  PathImage p(g, e);
  p.ToPpm("./example-data/ex_input_data/myTest.dat");
}