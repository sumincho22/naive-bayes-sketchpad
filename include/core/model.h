#pragma once

#include <ostream>

#include "image.h"

namespace naivebayes {

class Model {
 public:
  Model();

  friend std::ostream& operator<<(std::ostream& os, const std::vector<Image>& images);

 private:

};

}  // namespace naivebayes