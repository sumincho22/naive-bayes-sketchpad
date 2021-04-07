#pragma once

#include <ostream>

#include "image.h"
#include "data.h"

namespace naivebayes {

class Model {
 public:
  Model(Data data);

  void Train();

  // saving
  friend std::ostream& operator<<(std::ostream& os, const Model& model);

  // loading
  friend std::istream& operator>>(std::istream& is, Model& model);

 private:
  const char kProbDelim = '&';
  const char kShadeDelim = ',';
  const char kPixelDelim = '|';
  const char kLabelDelim = '*';

  const double kLaplaceSmoothing = 1.0;

  // Possible values: Shaded = 1 or Unshaded = 0
  const double kNumShades = 2.0;

  Data data_;

  std::vector<double> prior_probs_;
  std::vector<std::vector<std::vector<std::vector<double>>>> feature_probs_;

  void StorePriorProbs();

  void StoreFeatureProbs();

  double CalcPriorProb(const size_t label);

  double CalcFeatureProb(const size_t i, const size_t j, const size_t shade, const size_t label);

  // https://www.techiedelight.com/split-string-cpp-using-delimiter/
  void Split(const std::string& str, const char delim, std::vector<std::string>& out);

};

}  // namespace naivebayes