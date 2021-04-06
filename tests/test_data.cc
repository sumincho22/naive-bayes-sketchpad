#include <catch2/catch.hpp>

#include "core/image.h"
#include "core/data.h"

TEST_CASE("Data") {
 naivebayes::Data data(3);
 std::ifstream input_file("../../../data/testdata.txt");
 input_file >> data;
 REQUIRE(data.GetImages().size() == 3);
}