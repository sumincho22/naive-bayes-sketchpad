#include "core/model.h"

#include <utility>

namespace naivebayes {

Model::Model(Data data) : data_(std::move(data)) { }

//for (size_t i = 0; i < image_size_; ++i) {
//for (size_t j = 0; j < image_size_; ++j) {
//for (size_t shade = kUnshaded; shade <= kShaded; ++shade) {
//for (size_t label = 0; label < labels_.size(); ++label) {
//
//}
//}
//}
//}

double Model::CalcPriorProb(const size_t label) {
  double numerator = kLaplaceSmoothing + data_.GetNumImagesInClass(label);
  double denominator = data_.GetLabels().size() * kLaplaceSmoothing + data_.GetImages().size();
  return numerator / denominator;
}

double Model::CalcFeatureProb(const size_t i, const size_t j, const size_t shade, const size_t label) {
  double numerator = kLaplaceSmoothing + data_.GetCount(i, j, shade, label);
  double denominator = kNumShades * kLaplaceSmoothing + data_.GetNumImagesInClass(label);
  return numerator / denominator;
}

}