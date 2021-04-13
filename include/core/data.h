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

  /**
   * Loads dataset from input stream and creates a list of Images
   *
   * @param is      the input stream
   * @param data    the data object to modify
   * @return        the updated input stream
   */
  friend std::istream& operator>>(std::istream& is, Data& data);

  /**
   * Gets the number of images in a class
   *
   * @param label the class label
   * @return the number of images in a class
   */
  double GetNumImagesInClass(const size_t label) const;

  const size_t GetImageSize() const;
  const std::vector<Image>& GetImages() const;

 private:
  size_t kNumLabels = 10;

  size_t image_size_;
  std::vector<Image> images_;
  std::vector<size_t> num_images_in_class_;

  /**
   * Generates shade value for each pixel in Image
   *
   * @param pixels the dimensions of Image
   * @return the pixels with marked shade/unshaded values
   */
  std::vector<std::vector<size_t>> GetPixelShades(std::vector<std::string>& pixels) const;
};

}  // namespace naivebayes
