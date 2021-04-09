#include "core/image.h"

namespace naivebayes {

Image::Image(size_t label, const std::vector<std::vector<size_t>>& pixels) {
  label_ = label;
  pixels_ = pixels;
}

size_t Image::GetLabel() const {
  return label_;
}

size_t Image::GetShade(const size_t row, const size_t col) const {
  return pixels_[row][col];
}

}  // namespace naivebayes