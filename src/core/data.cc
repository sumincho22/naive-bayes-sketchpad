#include "core/data.h"

#include <string>

namespace naivebayes {

Data::Data(const size_t image_size) {
  image_size_ = image_size;
}

std::istream& operator>>(std::istream& is, Data& data) {
  std::string line;
  while (is.good()) {
    std::getline(is, line);
    size_t label = std::stoi(line);
    data.AddLabels(label);
    std::vector<std::string> pixel_lines;
    for (size_t i = 0; i < data.image_size_; i++) {
      std::getline(is, line);
      pixel_lines.emplace_back(line);
    }
    data.images_.emplace_back(Image(label, data.GetPixelShades(pixel_lines)));
  }
  return is;
}

std::vector<std::vector<size_t>> Data::GetPixelShades(std::vector<std::string>& pixel_lines) const {
  std::vector<std::vector<size_t>> pixel_shades(image_size_, std::vector<size_t> (image_size_, 0));
  for (size_t i = 0; i < image_size_; ++i) {
    for (size_t j = 0; j < image_size_; ++j) {
      switch(pixel_lines[i].at(j)) {
        case '+':
        case '#':
          pixel_shades[i][j] = kShaded;
          break;
        default:
          pixel_shades[i][j] = kUnshaded;
      }
    }
  }
  return pixel_shades;
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

double Data::GetCount(const size_t i, const size_t j, const size_t shade, const size_t label) const {
  double num_images = 0;
  for (const Image& image : images_) {
    if (image.GetLabel() == label && image.GetPixels()[i][j] == shade) {
      num_images++;
    }
  }
  return num_images;
}

void Data::AddLabels(const size_t label) {
  if (std::count(labels_.begin(), labels_.end(), label) == 0) {
    labels_.push_back(label);
  }
}

size_t Data::GetImageSize() const { return image_size_; }

const std::vector<Image>& Data::GetImages() const { return images_; }

const std::vector<size_t>& Data::GetLabels() const { return labels_; }

}
