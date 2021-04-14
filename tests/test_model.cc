#include <catch2/catch.hpp>

#include "core/image.h"
#include "core/data.h"
#include "core/model.h"

const size_t kImageSize = 3;
const size_t kNumImages = 4;
const size_t kLabel = 1;

const std::vector<std::vector<size_t>> kPixels
    {
        {kUnshaded, kShaded, kUnshaded},
        {kUnshaded, kShaded, kUnshaded},
        {kUnshaded, kShaded, kUnshaded}
    };

TEST_CASE("Train", "[train]") {
  naivebayes::Data data(3);
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
    REQUIRE(model.GetFeatureProb(0, 0, Pixel::kUnshaded, kLabel) == Approx(1.0/2.0).epsilon(.01));
    REQUIRE(model.GetFeatureProb(0, 1, Pixel::kUnshaded, kLabel) == Approx(1.0/4.0).epsilon(.01));
    REQUIRE(model.GetFeatureProb(0, 2, Pixel::kUnshaded, kLabel) == Approx(3.0/4.0).epsilon(.01));
    REQUIRE(model.GetFeatureProb(1, 0, Pixel::kUnshaded, kLabel) == Approx(3.0/4.0).epsilon(.01));
    REQUIRE(model.GetFeatureProb(1, 1, Pixel::kUnshaded, kLabel) == Approx(1.0/4.0).epsilon(.01));
    REQUIRE(model.GetFeatureProb(1, 2, Pixel::kUnshaded, kLabel) == Approx(3.0/4.0).epsilon(.01));
    REQUIRE(model.GetFeatureProb(2, 0, Pixel::kUnshaded, kLabel) == Approx(3.0/4.0).epsilon(.01));
    REQUIRE(model.GetFeatureProb(2, 1, Pixel::kUnshaded, kLabel) == Approx(1.0/4.0).epsilon(.01));
    REQUIRE(model.GetFeatureProb(2, 2, Pixel::kUnshaded, kLabel) == Approx(3.0/4.0).epsilon(.01));
  }
}

TEST_CASE("CalcLikelihoodScore", "[likelihood_score]") {
  naivebayes::Data data(3);
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
  naivebayes::Data data(3);
  std::ifstream input_file("../../../data/testdata_size3.txt");
  input_file >> data;
  naivebayes::Model model(data);
  model.Train();

 REQUIRE(model.Classify(kPixels) == 1);
}

TEST_CASE("CalcAccuracy", "[calc_accuracy]") {
  naivebayes::Data data(28);
  std::ifstream input_file("../../../data/trainingimagesandlabels.txt");
  input_file >> data;
  naivebayes::Model model(data);
  model.Train();

  naivebayes::Data test_data(28);
  std::ifstream test_file("../../../data/testimagesandlabels.txt");
  test_file >> test_data;

  double num_correct = 0;
  for (const naivebayes::Image& image : test_data.GetImages()) {
    if (model.Classify(image.GetPixels()) == image.GetLabel()) {
      num_correct++;
    }
  }

  double accuracy = model.CalcAccuracy(test_data.GetImages());
  REQUIRE(accuracy >= 0.7);
  REQUIRE(accuracy == num_correct / test_data.GetImages().size());
}