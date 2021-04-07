#include <catch2/catch.hpp>

#include "core/image.h"
#include "core/data.h"
#include "core/model.h"

const size_t kUnshaded = 0;
const size_t kShaded = 1;

const size_t kImageSize = 3;
const size_t kNumImages = 4;
const size_t kLabel = 1;
const size_t kNumLabels = 3;

TEST_CASE("Train", "[train]") {
  naivebayes::Data data(kImageSize);
  std::ifstream input_file("../../../data/testdata_size3.txt");
  input_file >> data;

  SECTION("Prior probabilities are properly stored") {

  }

  SECTION("Feature probabilities are properly stored") {

  }
}

TEST_CASE("Operator<<", "[op<<]") {

}

TEST_CASE("Operator>>", "[op>>]") {

}