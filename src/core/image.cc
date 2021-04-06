#include "core/image.h"

namespace naivebayes {

Image::Image(size_t label, const std::vector<std::vector<size_t>>& pixels) {
  label_ = label;
  pixels_ = pixels;
}

size_t Image::GetLabel() {
  return label_;
}

std::vector<std::vector<size_t>> Image::GetPixels() {
  return pixels_;
}

}  // namespace naivebayes