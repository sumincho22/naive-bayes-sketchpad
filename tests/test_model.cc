#include <catch2/catch.hpp>

#include "core/image.h"
#include "core/data.h"
#include "core/model.h"

const size_t kImageSize = 3;
const size_t kNumImages = 4;
const size_t kLabel = 1;
const size_t kNumLabels = 3;

TEST_CASE("Train", "[train]") {
  naivebayes::Data data(kImageSize);
  std::ifstream input_file("../../../data/testdata_size3.txt");
  input_file >> data;
  naivebayes::Model model(data);
  model.Train();

  SECTION("Prior probabilities are properly stored") {
    REQUIRE(model.GetPriorProb(1) == Approx(3.0/7.0).epsilon(.01));
    REQUIRE(model.GetPriorProb(7) == Approx(2.0/7.0).epsilon(.01));
    REQUIRE(model.GetPriorProb(0) == Approx(2.0/7.0).epsilon(.01));
  }

  SECTION("Feature probabilities are properly stored") {
//    REQUIRE(model.GetFeatureProb() == Approx(0.33).epsilon(.01));
//    REQUIRE(model.GetFeatureProb() == Approx(0.67).epsilon(.01));
//    REQUIRE(model.GetFeatureProb() == Approx(0.33).epsilon(.01));
//    REQUIRE(model.GetFeatureProb() == Approx(0.33).epsilon(.01));
//    REQUIRE(model.GetFeatureProb() == Approx(0.67).epsilon(.01));
//    REQUIRE(model.GetFeatureProb() == Approx(0.33).epsilon(.01));
//    REQUIRE(model.GetFeatureProb() == Approx(0.33).epsilon(.01));
//    REQUIRE(model.GetFeatureProb() == Approx(0.67).epsilon(.01));
//    REQUIRE(model.GetFeatureProb() == Approx(0.33).epsilon(.01));
  }
}