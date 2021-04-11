#include "core/data.h"

#include <string>
#include <iostream>

namespace naivebayes {

Data::Data(const size_t image_size) {
  image_size_ = image_size;
  images_ = std::vector<Image>();
  labels_ = std::vector<size_t>();
}

std::istream& operator>>(std::istream& is, Data& data) {
  std::string line;
  while (std::getline(is, line)) {
    size_t label = std::stoi(line);
    data.AddLabels(label);

    std::vector<std::string> image_rows;
    for (size_t i = 0; i < data.image_size_; ++i) {
      std::getline(is, line);
      image_rows.emplace_back(line);
    }

    data.images_.emplace_back(Image(label, data.image_size_, data.GetPixelShades(image_rows)));
  }
  return is;
}

std::vector<std::vector<size_t>> Data::GetPixelShades(std::vector<std::string>& image_rows) const {
  std::vector<std::vector<size_t>> pixels(image_size_, std::vector<size_t> (image_size_, 0));
  for (size_t i = 0; i < image_size_; ++i) {
    for (size_t j = 0; j < image_size_; ++j) {
      switch(image_rows[i].at(j)) {
        case '+':
        case '#':
          pixels[i][j] = Pixel::kShaded;
          break;
        default:
          pixels[i][j] = Pixel::kUnshaded;
      }
    }
  }
  return pixels;
}

double Data::GetNumImagesInClass(const size_t label) const {
  double num_images_in_class = 0;
  for (const Image& image : images_) {
    if (image.GetLabel() == label) {
      num_images_in_class++;
    }
  }
  return num_images_in_class;
}

double Data::GetCount(const size_t row, const size_t col, const size_t shade, const size_t label) const {
  double num_images = 0;
  for (const Image& image : images_) {
    if (image.GetLabel() == label && image.GetShade(row, col) == shade) {
      num_images++;
    }
  }
  return num_images;
}

const size_t Data::GetImageSize() const { return image_size_; }

const std::vector<Image>& Data::GetImages() const { return images_; }

const std::vector<size_t>& Data::GetLabels() const { return labels_; }

void Data::AddLabels(const size_t label) {
  if (std::count(labels_.begin(), labels_.end(), label) == 0) {
    labels_.push_back(label);
  }
}

}
