#include <catch2/catch.hpp>

#include "core/image.h"
#include "core/data.h"

const size_t kUnshaded = 0;
const size_t kShaded = 1;

const size_t kImageSize = 3;
const size_t kNumImages = 4;
const size_t kLabel = 1;
const size_t kNumLabels = 3;

TEST_CASE("Data operator overload", "[operator]") {
  SECTION("Overloading empty dataset throws error") {
    naivebayes::Data empty_data(0);
    std::ifstream empty_file("../../../data/emptydata.txt");
    REQUIRE_THROWS(empty_file >> empty_data);
  }
}

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
}

TEST_CASE("Test GetCount") {
  naivebayes::Data data(kImageSize);
  std::ifstream input_file("../../../data/testdata.txt");
  input_file >> data;

  SECTION("Test 1") {
    REQUIRE(data.GetCount(0, 0, kUnshaded, kLabel) == 1);
  }
}