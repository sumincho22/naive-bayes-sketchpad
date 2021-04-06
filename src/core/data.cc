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

}
