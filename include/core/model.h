#pragma once

#include <ostream>

#include "image.h"
#include "data.h"

namespace naivebayes {

using QuadVector = std::vector<std::vector<std::vector<std::vector<double>>>>;

/**
 * This class is a training model responsible for calculating probabilities and storing it. This class also
 * saves and loads data.
 */
class Model {
 public:
  /**
   * Creates a training model with the given dataset.
   *
   * @param data the dataset of the input file
   */
  Model(const Data& data);

  Model();

  /**
   * Trains the model.
   */
  void Train();

  double CalcAccuracy(const std::vector<Image>& images);

  size_t Classify(const std::vector<std::vector<size_t>>& pixels);

  double CalcLikelihoodScore(const std::vector<std::vector<size_t>>& pixels, const size_t label);

  /**
   * Saves the probabilities by writing them onto a .txt file
   *
   * @param os      output stream
   * @param model   the Model
   * @return        updated output stream
   */
  friend std::ostream& operator<<(std::ostream& os, const Model& model);

  /**
   * Loads the probabilities by reading the saved data from the .txt file
   *
   * @param is      input stream
   * @param model   the Model to modify
   * @return        updated input stream
   */
  friend std::istream& operator>>(std::istream& is, Model& model);

  double GetPriorProb(const size_t label) const;
  double GetFeatureProb(const size_t row, const size_t col, const size_t shade, const size_t label) const;

 private:
  const char kDelim = ' ';
  const double kLaplaceSmoothing = 1.0;
  const size_t kNumShades = 2;
  const size_t kNumLabels = 10;

  Data data_;
  std::vector<size_t> num_images_in_class_with_shade_;
  std::vector<double> prior_probs_;
  QuadVector feature_probs_;

  void StorePriorProbs();
  void StoreFeatureProbs();
  double CalcPriorProb(const size_t label);
  double CalcFeatureProb(const size_t label);
};

}  // namespace naivebayes