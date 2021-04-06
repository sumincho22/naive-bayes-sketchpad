#include "core/data.h"

#include <sstream>
#include <string>

namespace naivebayes {

Data::Data(const size_t image_size) {
  image_size_ = image_size;
}

std::istream& operator>>(std::istream& is, const Data& data) {
  std::string line;
  while (is.good()) {
    std::getline(is, line);
    size_t label = static_cast<size_t>(std::stoi(line));
    std::vector<std::string> pixels;
    for (size_t i = 0; i < data.image_size_; i++) {
      std::getline(is, line);
      pixels.emplace_back(line);
    }
    //data.images_.emplace_back(Image(label, ));
  }
  return is;
}

std::vector<std::vector<size_t>> Data::GetPixelShades(std::vector<std::string> pixels) {
  std::vector<std::vector<size_t>> pixel_shades(image_size_, std::vector<size_t> (image_size_, 0));
  for (size_t i = 0; i < image_size_; ++i) {
    for (size_t j = 0; j < image_size_; ++j) {
      switch(pixels.at(i).at(j)) {
        case '+':
        case '#':
          pixel_shades.at(i).at(j) = 1;
          break;
        default:
          pixel_shades.at(i).at(j) = 0;
      }
    }
  }
  return pixel_shades;
}

}
