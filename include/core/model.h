#pragma once

#include <ostream>

#include "image.h"

namespace naivebayes {

class Model {
 public:
  Model();

 private:
  void CalcPriorProb(const size_t label);

  void CalcFeatureProb();

};

}  // namespace naivebayes