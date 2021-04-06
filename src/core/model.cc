#include "core/model.h"

#include <utility>

namespace naivebayes {

Model::Model(Data data) : data_(std::move(data)) { }

void Model::Train() {
  StorePriorProbs();
  StoreFeatureProbs();
}

std::ostream& operator<<(std::ostream& os, const Model& model) {
  for (const double& prior_prob : model.prior_probs_) {
    os << prior_prob << std::endl;
  }

  os << model.kProbDelim;

  for (size_t label = 0; label < model.data_.GetLabels().size(); ++label) {
    os << std::endl;
    for (size_t i = 0; i < model.data_.GetImageSize(); ++i) {
      for (size_t j = 0; j < model.data_.GetImageSize(); ++j) {
        for (size_t shade = 0; shade <= model.kNumShades; ++shade) {
          double prob_value = model.feature_probs_[i][j][shade][label];
          if (shade == model.kNumShades) {
            os << prob_value;
          } else {
            os << prob_value << model.kShadeDelim;
          }
        }
        os << model.kPixelDelim;
      }
      os << std::endl;
    }
    if (label != model.data_.GetLabels().size() - 1) {
      os << model.kLabelDelim;
    }
  }
  return os;
}

void Model::StorePriorProbs() {
  for (size_t label = 0; label < data_.GetLabels().size(); ++label) {
    prior_probs_[label] = CalcPriorProb(label);
  }
}

void Model::StoreFeatureProbs() {
  for (size_t i = 0; i < data_.GetImageSize(); ++i) {
    for (size_t j = 0; j < data_.GetImageSize(); ++j) {
      for (size_t shade = 0; shade <= kNumShades; ++shade) {
        for (size_t label = 0; label < data_.GetLabels().size(); ++label) {
          feature_probs_[i][j][shade][label] = CalcFeatureProb(i, j, shade, label);
        }
      }
    }
  }
}

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