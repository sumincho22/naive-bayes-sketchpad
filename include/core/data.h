#pragma once

#include <fstream>

#include "image.h"

namespace naivebayes {

class Data {
 public:
  std::vector<size_t> num_images_in_class_;

  Data(const size_t image_size);

  const std::vector<std::vector<std::vector<std::vector<size_t>>>>& GetNumImagesInPixel() const;

  size_t GetImageSize() const;

  const std::vector<Image>& GetImages() const;

  friend std::istream& operator>>(std::istream& is, Data& data);

 private:
  size_t kUnshaded = 0;
  size_t kShaded = 1;

  size_t image_size_;
  std::vector<Image> images_;

  std::vector<std::vector<size_t>> GetPixelShades(std::vector<std::string>& pixels) const;

};

}
