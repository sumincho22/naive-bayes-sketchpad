#include <catch2/catch.hpp>

#include "core/image.h"
#include "core/data.h"
#include "core/model.h"

TEST_CASE("Data") {
//  SECTION("test data") {
//    naivebayes::Data data(3);
//    std::ifstream input_file("../../../data/testdata.txt");
//    input_file >> data;
//    REQUIRE(data.GetImages().size() == 3);
//  }

 SECTION("actual data") {
    naivebayes::Data data(28);
    std::ifstream input_file("../../../data/trainingimagesandlabels.txt");
    input_file >> data;
    REQUIRE(data.GetImages().size() == 5000);
 }

}