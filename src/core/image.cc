#include "core/image.h"

namespace naivebayes {

Image::Image(size_t label, const std::vector<std::vector<size_t>>& pixels) {
  label_ = label;
  pixels_ = pixels;
}

size_t Image::GetLabel() const {
  return label_;
}

std::vector<std::vector<size_t>> Image::GetPixels() const {
  return pixels_;
}

}  // namespace naivebayes