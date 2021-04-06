#include "core/model.h"

#include <utility>

namespace naivebayes {

Model::Model(Data data) : data_(std::move(data)) { }

double Model::CalcPriorProb(const size_t label) {
  return (kValue + data_.num_images_in_class_[label]) / (data_.num_images_in_class_.size() * kValue + data_.GetImages().size());
}

//double Model::CalcFeatureProb(const size_t shade, const size_t label) {
//  return (kValue + ) / (kPossibleValues * kValue + data_.num_images_in_class_[label]);
//}

}