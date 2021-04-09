#pragma once

#include <ostream>
#include <vector>

namespace naivebayes {

/**
 * This class holds data for an Image.
 */
class Image {
 public:
  /**
   * Creates an Image object with the given label and pixel shades.
   *
   * @param label   the class label of the Image
   * @param pixels  the pixel shades of the Image
   */
  Image(size_t label, const std::vector<std::vector<size_t>>& pixels);

  size_t GetLabel() const;

  size_t Image::GetShade(const size_t row, const size_t col) const;

 private:
  size_t label_;
  std::vector<std::vector<size_t>> pixels_;

};

}  // namespace naivebayes