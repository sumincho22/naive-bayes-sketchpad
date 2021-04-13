#include "core/model.h"

#include <utility>
#include <string>
#include <cmath>

namespace naivebayes {

Model::Model(const Data &data) : data_(data) {
  prior_probs_ = std::vector<double>(kNumLabels);
  feature_probs_ = QuadVector(data_.GetImageSize(), std::vector<std::vector<std::vector<double>>>(
      data_.GetImageSize(), std::vector<std::vector<double>>(kNumShades, std::vector<double>(
          kNumLabels))));
  num_images_in_class_with_shade_ = std::vector<size_t>(kNumLabels);
}

Model::Model() : data_(0) {}

void Model::Train() {
  StorePriorProbs();
  StoreFeatureProbs();
}

double Model::CalcAccuracy(const std::vector<Image> &images) {
  double num_correct = 0;
  for (const naivebayes::Image& image : images) {
    if (Classify(image.GetPixels()) == image.GetLabel()) {
      num_correct++;
    }
  }
  return num_correct / images.size();
}

size_t Model::Classify(const std::vector<std::vector<size_t>>& pixels) {
  size_t classifier = 0;
  double max_score = -1 * std::numeric_limits<double>::max();
  for (size_t label = 0; label < kNumLabels; ++label) {
    double score = CalcLikelihoodScore(pixels, label);
    if (score > max_score) {
      classifier = label;
      max_score = score;
    }
  }
  return classifier;
}

double Model::CalcLikelihoodScore(const std::vector<std::vector<size_t>>& pixels, const size_t label) {
  double likelihood_score = log(prior_probs_[label]);
  for (size_t i = 0; i < data_.GetImageSize(); ++i) {
    for (size_t j = 0; j < data_.GetImageSize(); ++j) {
      likelihood_score += log(feature_probs_[i][j][pixels[i][j]][label]);
    }
  }
  return likelihood_score;
}

std::ostream &operator<<(std::ostream &os, const Model &model) {
  os << model.data_.GetImageSize() << model.kDelim;

  for (const double prior_prob : model.prior_probs_) {
    os << prior_prob << model.kDelim;
  }

  for (size_t label = 0; label < model.kNumLabels; ++label) {
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

std::istream &operator>>(std::istream &is, Model &model) {
  model.prior_probs_.clear();
  model.feature_probs_.clear();

  size_t image_size;
  is >> image_size;

  model.prior_probs_.resize(model.kNumLabels);
  for (size_t i = 0; i < model.kNumLabels; ++i) {
    is >> model.prior_probs_[i];
  }

  model.feature_probs_ = QuadVector(image_size, std::vector<std::vector<std::vector<double>>>(
      image_size, std::vector<std::vector<double>>(model.kNumShades, std::vector<double>(
          model.kNumLabels))));
  for (size_t label = 0; label < model.kNumLabels; ++label) {
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
  for (size_t label = 0; label < kNumLabels; ++label) {
    prior_probs_[label] = CalcPriorProb(label);
  }
}

void Model::StoreFeatureProbs() {
  for (size_t i = 0; i < data_.GetImageSize(); ++i) {
    for (size_t j = 0; j < data_.GetImageSize(); ++j) {
      for (size_t shade = 0; shade < kNumShades; ++shade) {
        num_images_in_class_with_shade_.clear();
        num_images_in_class_with_shade_.resize(kNumLabels);

        for (const Image& image : data_.GetImages()) {
          if (image.GetShade(i, j) == shade) {
            num_images_in_class_with_shade_[image.GetLabel()]++;
          }
        }

        for (size_t label = 0; label < kNumLabels; ++label) {
          feature_probs_[i][j][shade][label] = CalcFeatureProb(label);
        }
      }
    }
  }
}

double Model::CalcPriorProb(const size_t label) {
  double numerator = kLaplaceSmoothing + data_.GetNumImagesInClass(label);
  double denominator = kNumLabels * kLaplaceSmoothing + data_.GetImages().size();
  return numerator / denominator;
}

double Model::CalcFeatureProb(const size_t label) {
  double numerator = kLaplaceSmoothing + num_images_in_class_with_shade_[label];
  double denominator = kNumShades * kLaplaceSmoothing + data_.GetNumImagesInClass(label);
  return numerator / denominator;
}

double Model::GetPriorProb(const size_t label) const {
  return prior_probs_[label];
}

double Model::GetFeatureProb(const size_t row, const size_t col, const size_t shade, const size_t label) const {
  return feature_probs_[row][col][shade][label];
}

}  // namespace naivebayes