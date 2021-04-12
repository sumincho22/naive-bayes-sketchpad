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
   * @param size    the size of the image
   * @param pixels  the pixel shades of the Image
   */
  Image(const size_t label, const size_t size, const std::vector<std::vector<size_t>>& pixels);

  const size_t& GetLabel() const;
  const size_t& GetSize() const;
  const std::vector<std::vector<size_t>>& GetPixels() const;
  size_t Image::GetShade(const size_t row, const size_t col) const;

 private:
  size_t label_;
  size_t size_;
  std::vector<std::vector<size_t>> pixels_;
};

}  // namespace naivebayes