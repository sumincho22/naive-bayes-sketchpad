#include "core/model.h"

#include <utility>

namespace naivebayes {

Model::Model(Data data) : data_(std::move(data)) { }

double Model::CalcPriorProb(const size_t label) {
  double numerator = kLaplaceSmoothing + data_.GetNumImagesInClass(label);
  double denominator = data_.GetLabels().size() * kLaplaceSmoothing + data_.GetImages().size();
  return numerator / denominator;
}

double Model::CalcFeatureProb(const size_t i, const size_t j, const size_t shade, const size_t label) {
  // return (kLaplaceSmoothing + data_.num_images_in_pixel_[i][j][label][shade]) / (kPossibleValues * kValue + data_.num_images_in_class_[label]);
}

}