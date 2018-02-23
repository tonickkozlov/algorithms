// Count the number of set bits in a number
#include <iostream>

#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

using namespace std;

int naiveCountBits(unsigned int x) {
  int count = 0;
  while (x) {
    count += (x & 1);
    x >>= 1;
  }
  return count;
}

int countBits(unsigned int x) {
  int count = 0;
  for (; x > 0; x &= (x-1)) {
    count++;
  }
  return count;
}

TEST_CASE("count bits") {
  REQUIRE(naiveCountBits(5) == 2);
  REQUIRE(countBits(5) == 2);
  REQUIRE(countBits(19) == 3);
  REQUIRE(countBits(20) == 2);
  REQUIRE(countBits(153) == 4);
}
