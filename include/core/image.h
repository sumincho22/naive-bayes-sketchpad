#include <ostream>
#include <vector>

namespace naivebayes {

class Image {
 public:
  Image();

  friend std::ostream& operator<<(std::ostream& os, const Image& image);

 private:
  std::vector<std::vector<size_t>> pixels_;

};

}  // namespace naivebayes