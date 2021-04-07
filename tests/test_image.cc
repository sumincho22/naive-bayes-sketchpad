#include <catch2/catch.hpp>

#include "core/image.h"

const size_t kUnshaded = 0;
const size_t kShaded = 1;

const size_t kLabel = 1;

TEST_CASE("Image Constructor", "[image_constructor]") {
  const std::vector<std::vector<size_t>> pixels
  {
      {kUnshaded, kShaded, kUnshaded},
      {kUnshaded, kShaded, kUnshaded},
      {kUnshaded, kShaded, kUnshaded}
  };
  naivebayes::Image image(kLabel, pixels);
  REQUIRE(image.GetLabel() == kLabel);
  REQUIRE(image.GetPixels() == pixels);
}