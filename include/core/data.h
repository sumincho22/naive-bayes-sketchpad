#pragma once

#include <fstream>

#include "image.h"

namespace naivebayes {

class Data {
 public:
  Data(const size_t image_size);

  double GetNumImagesInClass(const size_t label) const;

  size_t GetImageSize() const;

  const std::vector<Image>& GetImages() const;

  const std::vector<size_t>& GetLabels() const;

  double GetCount(const size_t i, const size_t j, const size_t shade, const size_t label) const;

  friend std::istream& operator>>(std::istream& is, Data& data);

 private:
  size_t kUnshaded = 0;
  size_t kShaded = 1;

  size_t image_size_;
  std::vector<Image> images_;
  std::vector<size_t> labels_;

  std::vector<std::vector<size_t>> GetPixelShades(std::vector<std::string>& pixels) const;

  void AddLabels(const size_t label);

};

}
