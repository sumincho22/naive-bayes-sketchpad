#include <catch2/catch.hpp>

#include "core/image.h"
#include "core/data.h"

const size_t kImageSize = 3;
const size_t kImageSize2 = 4;

const size_t kNumImages = 4;
const size_t kLabel = 1;

const std::string kFileEmptyData = "../../../data/emptydata.txt";
const std::string kFilePath3by3 = "../../../data/testdata_size3.txt";
const std::string kFilePath4by4 = "../../../data/testdata_size4.txt";

TEST_CASE("Data operator overload", "[operator]") {
  naivebayes::Data data(kImageSize);
  std::ifstream input_file(kFilePath3by3);
  input_file >> data;

  SECTION("Check number of images") {
    REQUIRE(data.GetImages().size() == kNumImages);
  }

  SECTION("Check image size") {
    REQUIRE(data.GetImages()[0].GetSize() == kImageSize);
  }
}

TEST_CASE("Check empty dataset") {
  naivebayes::Data empty_data(0);
  std::ifstream empty_file(kFileEmptyData);
  empty_file >> empty_data;

  REQUIRE(empty_data.GetImageSize() == 0);
  REQUIRE(empty_data.GetImages().size() == 0);
}

TEST_CASE("Check 4 by 4 dataset", "[4by4]") {
  naivebayes::Data data(kImageSize2);
  std::ifstream input_file(kFilePath4by4);
  input_file >> data;

  REQUIRE(data.GetImageSize() == kImageSize2);
  REQUIRE(data.GetImages().size() == kNumImages);
  REQUIRE(data.GetImages()[1].GetLabel() == 2);
}

TEST_CASE("Check each image in dataset", "[images]") {
  naivebayes::Data data(kImageSize);
  std::ifstream input_file(kFilePath3by3);
  input_file >> data;

  REQUIRE(data.GetImages()[0].GetLabel() == 1);
  REQUIRE(data.GetImages()[1].GetLabel() == 7);
  REQUIRE(data.GetImages()[2].GetLabel() == 0);
  REQUIRE(data.GetImages()[3].GetLabel() == 1);
}

TEST_CASE("GetNumImagesInClass") {
  naivebayes::Data data(kImageSize);
  std::ifstream input_file(kFilePath3by3);
  input_file >> data;

  SECTION("Check for class label without images") {
    REQUIRE(data.GetNumImagesInClass(9) == 0);
    REQUIRE(data.GetNumImagesInClass(2) == 0);
  }

  SECTION("Check each label for number of images") {
    REQUIRE(data.GetNumImagesInClass(0) == 1);
    REQUIRE(data.GetNumImagesInClass(1) == 2);
    REQUIRE(data.GetNumImagesInClass(7) == 1);
  }
}