#pragma once

#include <ostream>

#include "image.h"
#include "data.h"

namespace naivebayes {

class Model {
 public:
  Model(Data data);

 private:
  const double kValue = 1.0;
  const double kPossibleValues = 2.0;

  Data data_;

  double CalcPriorProb(const size_t label);

  double CalcFeatureProb(const size_t shade, const size_t label);

};

}  // namespace naivebayes