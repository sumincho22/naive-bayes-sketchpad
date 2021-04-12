#include "core/image.h"

namespace naivebayes {

Image::Image(const size_t label, const size_t size, const std::vector<std::vector<size_t>>& pixels) {
  label_ = label;
  size_ = size;
  pixels_ = pixels;
}

const size_t& Image::GetLabel() const {
  return label_;
}

const size_t& Image::GetSize() const {
  return size_;
}

const std::vector<std::vector<size_t>>& Image::GetPixels() const {
  return pixels_;
}

size_t Image::GetShade(const size_t row, const size_t col) const {
  return pixels_[row][col];
}

}  // namespace naivebayes