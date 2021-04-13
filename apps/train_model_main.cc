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

  std::cout << model.CalcAccuracy(test_data.GetImages());
}