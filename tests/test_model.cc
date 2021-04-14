#include <catch2/catch.hpp>
#include <iostream>

#include "core/image.h"
#include "core/data.h"
#include "core/model.h"

const double kMinAccuracy = 0.7;
const size_t kTestSize = 3;
const size_t kActualSize = 28;
const std::vector<std::vector<size_t>> kPixels
    {
        {kUnshaded, kShaded, kUnshaded},
        {kUnshaded, kShaded, kUnshaded},
        {kUnshaded, kShaded, kUnshaded}
    };

TEST_CASE("Train", "[train]") {
  naivebayes::Data data(kTestSize);
  std::ifstream input_file("../../../data/testdata_size3.txt");
  input_file >> data;
  naivebayes::Model model(data);
  model.Train();

  SECTION("Prior probabilities are properly stored") {
    REQUIRE(model.GetPriorProb(1) == Approx(3.0/14.0).epsilon(.01));
    REQUIRE(model.GetPriorProb(7) == Approx(2.0/14.0).epsilon(.01));
    REQUIRE(model.GetPriorProb(0) == Approx(2.0/14.0).epsilon(.01));
  }

  SECTION("Feature probabilities are properly stored") {
    REQUIRE(model.GetFeatureProb(0, 0, kUnshaded, 1) == Approx(1.0/2.0).epsilon(.01));
    REQUIRE(model.GetFeatureProb(0, 1, kUnshaded, 1) == Approx(1.0/4.0).epsilon(.01));
    REQUIRE(model.GetFeatureProb(0, 2, kUnshaded, 1) == Approx(3.0/4.0).epsilon(.01));
    REQUIRE(model.GetFeatureProb(1, 0, kUnshaded, 1) == Approx(3.0/4.0).epsilon(.01));
    REQUIRE(model.GetFeatureProb(1, 1, kUnshaded, 1) == Approx(1.0/4.0).epsilon(.01));
    REQUIRE(model.GetFeatureProb(1, 2, kUnshaded, 1) == Approx(3.0/4.0).epsilon(.01));
    REQUIRE(model.GetFeatureProb(2, 0, kUnshaded, 1) == Approx(3.0/4.0).epsilon(.01));
    REQUIRE(model.GetFeatureProb(2, 1, kUnshaded, 1) == Approx(1.0/4.0).epsilon(.01));
    REQUIRE(model.GetFeatureProb(2, 2, kUnshaded, 1) == Approx(3.0/4.0).epsilon(.01));
  }
}

// NOTE: Make sure to empty test_file.txt before running this test
TEST_CASE("operator<<", "[op<<]") {
  naivebayes::Data data(kTestSize);
  std::ifstream input_file("../../../data/testdata_size3.txt");
  input_file >> data;
  naivebayes::Model model(data);
  model.Train();

  std::fstream test_file("../../../data/test_file.txt");
  test_file << model;
  test_file.close();

  test_file.open("../../../data/test_file.txt");
  size_t first_value;
  test_file >> first_value;

  REQUIRE(first_value == kTestSize);
}

// NOTE: Data is already saved on the file this text is using
TEST_CASE("operator>>", "[op>>]") {
  naivebayes::Model model(3);
  std::ifstream is;
  is.open("../../../data/test_load_file.txt");
  is >> model;

  SECTION("Check prior probabilities after load") {
    REQUIRE(model.GetPriorProb(1) == Approx(3.0/14.0).epsilon(.01));
    REQUIRE(model.GetPriorProb(7) == Approx(2.0/14.0).epsilon(.01));
    REQUIRE(model.GetPriorProb(0) == Approx(2.0/14.0).epsilon(.01));
  }

  SECTION("Check feature probabilities after load") {
    REQUIRE(model.GetFeatureProb(0, 0, kUnshaded, 1) == Approx(1.0/2.0).epsilon(.01));
    REQUIRE(model.GetFeatureProb(0, 1, kUnshaded, 1) == Approx(1.0/4.0).epsilon(.01));
    REQUIRE(model.GetFeatureProb(0, 2, kUnshaded, 1) == Approx(3.0/4.0).epsilon(.01));
    REQUIRE(model.GetFeatureProb(1, 0, kUnshaded, 1) == Approx(3.0/4.0).epsilon(.01));
    REQUIRE(model.GetFeatureProb(1, 1, kUnshaded, 1) == Approx(1.0/4.0).epsilon(.01));
    REQUIRE(model.GetFeatureProb(1, 2, kUnshaded, 1) == Approx(3.0/4.0).epsilon(.01));
    REQUIRE(model.GetFeatureProb(2, 0, kUnshaded, 1) == Approx(3.0/4.0).epsilon(.01));
    REQUIRE(model.GetFeatureProb(2, 1, kUnshaded, 1) == Approx(1.0/4.0).epsilon(.01));
    REQUIRE(model.GetFeatureProb(2, 2, kUnshaded, 1) == Approx(3.0/4.0).epsilon(.01));
  }
}

TEST_CASE("CalcLikelihoodScore", "[likelihood_score]") {
  naivebayes::Data data(kTestSize);
  std::ifstream input_file("../../../data/testdata_size3.txt");
  input_file >> data;
  naivebayes::Model model(data);
  model.Train();

  REQUIRE(model.CalcLikelihoodScore(kPixels, 0) == Approx(-10.4471).epsilon(.01));
  REQUIRE(model.CalcLikelihoodScore(kPixels, 1) == Approx(-4.53505).epsilon(.01));
  REQUIRE(model.CalcLikelihoodScore(kPixels, 7) == Approx(-8.36768).epsilon(.01));

  // For class labels that are not in the dataset
  REQUIRE(model.CalcLikelihoodScore(kPixels, 9) == Approx(-8.87738).epsilon(.01));
  REQUIRE(model.CalcLikelihoodScore(kPixels, 5) == Approx(-8.87738).epsilon(.01));
}

TEST_CASE("Classify", "[classify]") {
  naivebayes::Data data(kTestSize);
  std::ifstream input_file("../../../data/testdata_size3.txt");
  input_file >> data;
  naivebayes::Model model(data);
  model.Train();

 REQUIRE(model.Classify(kPixels) == 1);
}

TEST_CASE("CalcAccuracy", "[calc_accuracy]") {
  naivebayes::Data data(kActualSize);
  std::ifstream input_file("../../../data/trainingimagesandlabels.txt");
  input_file >> data;
  naivebayes::Model model(data);
  model.Train();

  naivebayes::Data test_data(kActualSize);
  std::ifstream test_file("../../../data/testimagesandlabels.txt");
  test_file >> test_data;

  double num_correct = 0;
  for (const naivebayes::Image& image : test_data.GetImages()) {
    if (model.Classify(image.GetPixels()) == image.GetLabel()) {
      num_correct++;
    }
  }

  double accuracy = model.CalcAccuracy(test_data.GetImages());
  REQUIRE(accuracy >= kMinAccuracy);
  REQUIRE(accuracy == num_correct / test_data.GetImages().size());
}