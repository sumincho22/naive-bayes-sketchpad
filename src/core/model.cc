#include "core/model.h"

#include <utility>
#include <string>
#include <iostream>

namespace naivebayes {

Model::Model(Data data) : data_(std::move(data)) {
  prior_probs_ = std::vector<double>(data_.GetLabels().size());
  feature_probs_ = QuadVector(data_.GetImageSize(), std::vector<std::vector<std::vector<double>>>
      (data_.GetImageSize(), std::vector<std::vector<double>>
      (kNumShades, std::vector<double>
          (data_.GetLabels().size()))));
}

void Model::Train() {
  StorePriorProbs();
  StoreFeatureProbs();
}

std::ostream& operator<<(std::ostream& os, const Model& model) {
  for (const double prior_prob : model.prior_probs_) {
    os << prior_prob << std::endl;
  }

  os << model.kProbDelim;

  for (size_t label = 0; label < model.data_.GetLabels().size(); ++label) {
    os << std::endl;
    for (size_t i = 0; i < model.data_.GetImageSize(); ++i) {
      for (size_t j = 0; j < model.data_.GetImageSize(); ++j) {
        for (size_t shade = 0; shade < model.kNumShades; ++shade) {
          double prob_value = model.feature_probs_[i][j][shade][label];
          if (shade == Pixel::kShaded) {
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

std::istream& operator>>(std::istream& is, Model& model) {
  std::string line;

  // Loading prior probabilities
  size_t index = 0;
  while (std::getline(is, line) && line[0] == model.kProbDelim) {
    model.prior_probs_.push_back(std::stod(line));
    index++;
  }

  size_t label = 0;
  size_t i = 0;
  while (std::getline(is, line)) {
    if (line[0] == model.kLabelDelim) {
      label++;
      i = 0;
      continue;
    }

    std::vector<std::string> pixels;
    model.Split(line, model.kPixelDelim, pixels);
    size_t j = 0;
    for (const std::string& pixel : pixels) {
      std::vector<std::string> shades;
      model.Split(pixel, model.kShadeDelim, shades);

      size_t shade_count = 0;
      for (const std::string& shade : shades) {
        double feature_prob = std::stod(shade);
        model.feature_probs_[i][j][shade_count][label] = feature_prob;
        shade_count++;
      }
      j++;
    }
    i++;
  }
  return is;
}

void Model::StorePriorProbs() {
  for (size_t i = 0; i < data_.GetLabels().size(); ++i) {
    size_t label = data_.GetLabels()[i];
    prior_probs_[i] = CalcPriorProb(label);
  }
}

void Model::StoreFeatureProbs() {
  for (size_t i = 0; i < data_.GetImageSize(); ++i) {
    for (size_t j = 0; j < data_.GetImageSize(); ++j) {
      for (size_t shade = 0; shade < kNumShades; ++shade) {
        for (size_t label_index = 0; label_index < data_.GetLabels().size(); ++label_index) {
          size_t label = data_.GetLabels()[label_index];
          feature_probs_[i][j][shade][label_index] = CalcFeatureProb(i, j, shade, label);
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

void Model::Split(const std::string& str, const char delim, std::vector<std::string>& out) {
  size_t start;
  size_t end = 0;

  while ((start = str.find_first_not_of(delim, end)) != std::string::npos) {
    end = str.find(delim, start);
    out.push_back(str.substr(start, end - start));
  }
}

double Model::GetPriorProb(const size_t label) const {
  for (size_t i = 0; i < data_.GetLabels().size(); ++i) {
    if (data_.GetLabels()[i] == label) {
      return prior_probs_[i];
    }
  }
  return 0;
}

double Model::GetFeatureProb(const size_t row, const size_t col, const size_t shade, const size_t label) const {
  return feature_probs_[row][col][shade][label];
}

}