#include <catch2/catch.hpp>

#include "core/pixel.h"
#include "core/image.h"

const size_t kImageSize = 3;
const size_t kLabel = 1;

const std::vector<std::vector<size_t>> kPixels
    {
        {kUnshaded, kShaded, kUnshaded},
        {kUnshaded, kShaded, kUnshaded},
        {kUnshaded, kShaded, kUnshaded}
    };

TEST_CASE("Image Constructor", "[image_constructor]") {
  naivebayes::Image image(kLabel, kImageSize, kPixels);
  REQUIRE(image.GetLabel() == kLabel);
  REQUIRE(image.GetPixels() == kPixels);
}

TEST_CASE("GetShade") {
  naivebayes::Image image(kLabel, kImageSize, kPixels);
  REQUIRE(image.GetShade(0, 0) == kUnshaded);
  REQUIRE(image.GetShade(0, 1) == kShaded);
  REQUIRE(image.GetShade(0, 2) == kUnshaded);
  REQUIRE(image.GetShade(1, 0) == kUnshaded);
  REQUIRE(image.GetShade(1, 1) == kShaded);
  REQUIRE(image.GetShade(1, 2) == kUnshaded);
  REQUIRE(image.GetShade(2, 0) == kUnshaded);
  REQUIRE(image.GetShade(2, 1) == kShaded);
  REQUIRE(image.GetShade(2, 2) == kUnshaded);
}