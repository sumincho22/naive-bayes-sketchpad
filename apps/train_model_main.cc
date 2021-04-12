#include <iostream>
#include <fstream>

#include "core/data.h"
#include "core/model.h"
#include "core/image.h"

int main() {
  // TODO: Replace this with code that reads the training data, trains a model,
  // and saves the trained model to a file.
  naivebayes::Data data(3);
  std::ifstream input_file("../data/testdata_size3.txt");
  input_file >> data;
  naivebayes::Model model(data);
//  model.Train();

//  std::ofstream save_file;
//  save_file.open("../data/testsave.txt");
//  save_file << model;

  std::ifstream load_file;
  load_file.open("../data/testsave.txt");
  if (load_file.is_open()) {
    load_file >> model;
  }
  load_file.close();
}