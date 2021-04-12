#include <iostream>

#include "core/data.h"
#include "core/model.h"

int main() {
  naivebayes::Data data(28);
  std::ifstream input_file("../data/trainingimagesandlabels.txt");
  input_file >> data;
  naivebayes::Model model(data);
  model.Train();

  naivebayes::Data test_data(28);
  std::ifstream test_file("../data/testimagesandlabels.txt");
  test_file >> test_data;

  double num_correct = 0;
  for (const naivebayes::Image& image : test_data.GetImages()) {
    if (image.GetLabel() == model.Classify(image.GetPixels())) {
      num_correct++;
    }
  }
  double accuracy = num_correct / test_data.GetImages().size();
  std::cout << accuracy;
}