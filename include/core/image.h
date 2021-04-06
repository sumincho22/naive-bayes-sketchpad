#include <ostream>
#include <vector>

namespace naivebayes {

class Image {
 public:
  Image(size_t label, const std::vector<std::vector<size_t>>& pixels);

  size_t GetLabel();

  std::vector<std::vector<size_t>> GetPixels();

 private:
  size_t label_;
  std::vector<std::vector<size_t>> pixels_;

};

}  // namespace naivebayes