#include <catch2/catch.hpp>

#include "core/image.h"
#include "core/data.h"

const size_t kImageSize = 3;
const size_t kImageSize2 = 4;
const size_t kImageSize3 = 5;

const size_t kNumImages = 4;
const size_t kLabel = 1;
const size_t kNumLabels = 3;

const std::string kFilePath3by3 = "../../../data/testdata_size3.txt";
const std::string kFilePath4by4 = "../../../data/testdata_size4.txt";
const std::string kFilePath5by5 = "../../../data/testdata_size5.txt";

TEST_CASE("Data operator overload", "[operator]") {
  naivebayes::Data data(kImageSize);
  std::ifstream input_file(kFilePath3by3);
  input_file >> data;

//  SECTION("Overloading empty dataset throws error") {
//    naivebayes::Data empty_data(0);
//    std::ifstream empty_file("../../../data/emptydata.txt");
//    REQUIRE_THROWS(empty_file >> empty_data);
//  }

  SECTION("Check number of images") {
    REQUIRE(data.GetImages().size() == kNumImages);
  }

  SECTION("Check number of images in a certain class") {
    REQUIRE(data.GetNumImagesInClass(kLabel) == 2);
  }

  SECTION("Check image size") {
    REQUIRE(data.GetImages()[0].GetSize() == kImageSize);
  }
}

TEST_CASE("Check 4 by 4 dataset", "[4by4]") {
  naivebayes::Data data(kImageSize2);
  std::ifstream input_file(kFilePath4by4);
  input_file >> data;

  REQUIRE(data.GetImages()[0].GetSize() == kImageSize2);
  REQUIRE(data.GetImages().size() == kNumImages);
  REQUIRE(data.GetImages()[1].GetLabel() == 2);
}