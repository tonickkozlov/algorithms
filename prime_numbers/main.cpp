// Find all prime numbers that are smaller then the fiven number

#include <vector>
#include <string>
#include <limits>
#include <iostream>
#include <set>
#include <queue>
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

using namespace std;

// sieve of eratosthenes
vector<int> findPrimes(int n) {
  vector<int> numbers;
  vector<int> res;
  for (int i = 0; i <= n; i++) {
    numbers.push_back(i);
  }
  int i = 2;
  while (i < numbers.size()) {
    // p is the next numbers number.
    for (int x = 2; i * x <= n; x++) {
      int target = i*x;
      if (numbers[target] > 0) {
        numbers[target] *= -1; // mark number as negative (someone's factor)
      }
    }
    // move for the next unmarked number
    i++;
    while (i < numbers.size() && numbers[i] < 0) {
      i++;
    }
  }
  for (int i = 2; i < numbers.size(); i++) {
    if (numbers[i] > 0) {
      res.push_back(numbers[i]);
    }
  }
  return res;
}

TEST_CASE("prime-numbers") {
  const int n = 50;
  vector<int> target = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
  REQUIRE(findPrimes(n) == target);
}
