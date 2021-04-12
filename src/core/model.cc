#include "core/model.h"

#include <utility>
#include <string>
#include <math.h>

namespace naivebayes {

Model::Model(const Data& data) : data_(data) {
  image_labels_ = data.GetLabels();
  prior_probs_ = std::vector<double>(image_labels_.size());
  feature_probs_ = QuadVector(data_.GetImageSize(), std::vector<std::vector<std::vector<double>>>(
      data_.GetImageSize(), std::vector<std::vector<double>>(kNumShades,std::vector<double>(
          image_labels_.size()))));
}

void Model::Train() {
  StorePriorProbs();
  StoreFeatureProbs();
}

size_t Model::Classify(const Image &image) {

}

double Model::CalcLikelihoodScore(const Image& image, const size_t label) {
  double likelihood_score = log(CalcPriorProb(label));
  for (size_t i = 0; i < data_.GetImageSize(); ++i) {
    for (size_t j = 0; j < data_.GetImageSize(); ++j) {
      likelihood_score += log(CalcFeatureProb(i, j, image.GetShade(i, j), label));
    }
  }
  return likelihood_score;
}

std::ostream& operator<<(std::ostream& os, const Model& model) {
  os << model.data_.GetImageSize() << model.kDelim;
  os << model.image_labels_.size() << model.kDelim;

  for (const size_t image_label : model.image_labels_) {
    os << image_label << model.kDelim;
  }

  for (const double prior_prob : model.prior_probs_) {
    os << prior_prob << model.kDelim;
  }

  for (size_t label = 0; label < model.image_labels_.size(); ++label) {
    for (size_t i = 0; i < model.data_.GetImageSize(); ++i) {
      for (size_t j = 0; j < model.data_.GetImageSize(); ++j) {
        for (size_t shade = 0; shade < model.kNumShades; ++shade) {
          os << model.feature_probs_[i][j][shade][label] << model.kDelim;
        }
      }
    }
  }
  return os;
}

std::istream& operator>>(std::istream& is, Model& model) {
  model.image_labels_.clear();
  model.prior_probs_.clear();
  model.feature_probs_.clear();

  size_t image_size;
  size_t num_labels;

  is >> image_size;
  is >> num_labels;

  for (size_t i = 0; i < num_labels; ++i) {
    is >> model.image_labels_[i];
  }

  for (size_t i = 0; i < num_labels; ++i) {
    is >> model.prior_probs_[i];
  }

  for (size_t label = 0; label < num_labels; ++label) {
    for (size_t i = 0; i < image_size; ++i) {
      for (size_t j = 0; j < image_size; ++j) {
        for (size_t shade = 0; shade < model.kNumShades; ++shade) {
          is >> model.feature_probs_[i][j][shade][label];
        }
      }
    }
  }
  return is;
}

void Model::StorePriorProbs() {
  for (size_t i = 0; i < image_labels_.size(); ++i) {
    size_t label = image_labels_[i];
    prior_probs_[i] = CalcPriorProb(label);
  }
}

void Model::StoreFeatureProbs() {
  for (size_t i = 0; i < data_.GetImageSize(); ++i) {
    for (size_t j = 0; j < data_.GetImageSize(); ++j) {
      for (size_t shade = 0; shade < kNumShades; ++shade) {
        for (size_t label_index = 0; label_index < image_labels_.size(); ++label_index) {
          size_t label = image_labels_[label_index];
          feature_probs_[i][j][shade][label_index] = CalcFeatureProb(i, j, shade, label);
        }
      }
    }
  }
}

double Model::CalcPriorProb(const size_t label) {
  double numerator = kLaplaceSmoothing + data_.GetNumImagesInClass(label);
  double denominator = image_labels_.size() * kLaplaceSmoothing + data_.GetImages().size();
  return numerator / denominator;
}

double Model::CalcFeatureProb(const size_t i, const size_t j, const size_t shade, const size_t label) {
  double numerator = kLaplaceSmoothing + data_.GetCount(i, j, shade, label);
  double denominator = kNumShades * kLaplaceSmoothing + data_.GetNumImagesInClass(label);
  return numerator / denominator;
}

double Model::GetPriorProb(const size_t label) const {
  for (size_t i = 0; i < image_labels_.size(); ++i) {
    if (image_labels_[i] == label) {
      return prior_probs_[i];
    }
  }
  return 0;
}

double Model::GetFeatureProb(const size_t row, const size_t col, const size_t shade, const size_t label) const {
  size_t label_index = 0;
  for (size_t i = 0; i < image_labels_.size(); ++i) {
    if (image_labels_[i] == label) {
      label_index = i;
      break;
    }
  }
  return feature_probs_[row][col][shade][label_index];
}

}  // namespace naivebayes