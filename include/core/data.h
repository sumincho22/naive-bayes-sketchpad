#pragma once

#include <fstream>

#include "image.h"

namespace naivebayes {

class Data {
 public:
  Data(const size_t image_size);

  friend std::istream& operator>>(std::istream& is, Data data);

  std::vector<std::vector<size_t>> GetPixelShades(std::vector<std::string> pixels);

 private:
  size_t image_size_;
  std::vector<Image> images_;

};

}
