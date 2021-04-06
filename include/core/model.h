#pragma once

#include <ostream>

#include "image.h"
#include "data.h"

namespace naivebayes {

class Model {
 public:
  Model(Data data);

  double CalcPriorProb(const size_t label);

  double CalcFeatureProb(const size_t i, const size_t j, const size_t shade, const size_t label);

 private:
  const double kLaplaceSmoothing = 1.0;

  // Shaded or Unshaded
  const double kPossibleValues = 2.0;

  Data data_;

};

}  // namespace naivebayes