#include <catch2/catch.hpp>

#include "core/image.h"
#include "core/data.h"
#include "core/model.h"

const size_t kImageSize = 3;
const size_t kNumImages = 4;
const size_t kLabel = 1;
const size_t kNumLabels = 3;

TEST_CASE("Images in dataset", "[images]") {
  naivebayes::Data data(kImageSize);
  std::ifstream input_file("../../../data/testdata.txt");
  input_file >> data;

  SECTION("Check number of images") {
    REQUIRE(data.GetImages().size() == kNumImages);
  }

  SECTION("GetNumImagesInClass method") {
    REQUIRE(data.GetNumImagesInClass(kLabel) == 2);
  }

  SECTION("Check image size") {
    REQUIRE(data.GetImageSize() == kImageSize);
  }
}

TEST_CASE("Labels in dataset", "[labels]") {
  naivebayes::Data data(kImageSize);
  std::ifstream input_file("../../../data/testdata.txt");
  input_file >> data;

  SECTION("Check number of labels") {
    REQUIRE(data.GetLabels().size() == kNumLabels);
  }

  SECTION("Check number of labels in empty dataset") {
    naivebayes::Data empty_data(0);
    std::ifstream empty_file("../../../data/emptydata.txt");
    REQUIRE_THROWS(empty_file >> empty_data);
  }
}