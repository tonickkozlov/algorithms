// Count the number of set bits in a number
#include <iostream>

#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

using namespace std;

long factorial(int x) {
  long tmp = 1;
  for (int i = 2; i <= x; i++) {
    tmp *= i;
  }
  return tmp;
}

TEST_CASE("count bits") {
  REQUIRE(factorial(4) == 24);
  REQUIRE(factorial(5) == 120);
  REQUIRE(factorial(6) == 720);

  for (int i = 7; i < 40; i++) {
    cout << i << " : " << factorial(i) << endl;
  }
}
