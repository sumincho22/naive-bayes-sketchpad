#pragma once

#include <fstream>

#include "pixel.h"
#include "image.h"

namespace naivebayes {

/**
 * This class holds the dataset of the images in the input file. This class is also responsible for
 * computing data for the provided set of images.
 */
class Data {
 public:
  /**
   * Creates a Data object
   *
   * @param image_size the size of the square image in dataset
   */
  Data(const size_t image_size);

  double GetNumImagesInClass(const size_t label) const;

  size_t GetImageSize() const;

  const std::vector<Image>& GetImages() const;

  const std::vector<size_t>& GetLabels() const;

  /**
   * Gets the count of the images in a certain class with the specific pixel shade
   *
   * @param row       the row of image pixels
   * @param col       the column of image pixels
   * @param shade   the value for shaded or unshaded (1 or 0 respectively)
   * @param label   the class label for the given image
   * @return        the number of images in a certain class with the specific pixel shade
   */
  double GetCount(const size_t row, const size_t col, const size_t shade, const size_t label) const;

  /**
   * Loads dataset from input stream and creates a list of Images
   *
   * @param is      the input stream
   * @param data    the data object to modify
   * @return        the updated input stream
   */
  friend std::istream& operator>>(std::istream& is, Data& data);

 private:
  size_t image_size_;
  std::vector<Image> images_;
  std::vector<size_t> labels_;

  /**
   * Generates shade value for each pixel in Image
   *
   * @param pixels the dimensions of Image
   * @return the pixels with marked shade/unshaded values
   */
  std::vector<std::vector<size_t>> GetPixelShades(std::vector<std::string>& pixels) const;

  /**
   * Adds a label to a vector of labels
   *
   * @param label the class for an image
   */
  void AddLabels(const size_t label);

};

}
