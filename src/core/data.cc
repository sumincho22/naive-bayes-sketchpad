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

    std::vector<std::string> pixel_lines;
    for (size_t i = 0; i < data.image_size_; i++) {
      std::getline(is, line);
      pixel_lines.emplace_back(line);
    }

    data.num_images_in_class_[label]++;

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

const std::vector<std::vector<std::vector<std::vector<size_t>>>>& Data::GetNumImagesInPixel() const {
  std::vector<std::vector<std::vector<std::vector<size_t>>>> num_images_in_pixel;
  for (size_t i = 0; i < image_size_; ++i) {
    for (size_t j = 0; j < image_size_; ++j) {
      for (size_t label = 0; label < num_images_in_class_.size(); ++label) {
        std::vector<Image> images_in_class;
        for (Image image : images_) {
          if (image.GetLabel() == label) {
            images_in_class.emplace_back(image);
          }
        }
        for (Image image_in_class : images_in_class) {
          if (image_in_class.GetPixels()[i][j] == kShaded) {
            num_images_in_pixel[i][j][label][kShaded]++;
          } else {
            num_images_in_pixel[i][j][label][kUnshaded]++;
          }
        }
      }
    }
  }
  return num_images_in_pixel;
}

size_t Data::GetImageSize() const { return image_size_; }

const std::vector<Image>& Data::GetImages() const { return images_; }

}
