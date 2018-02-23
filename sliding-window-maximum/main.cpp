// Given an array and an integer k, find the maximum for each and every contiguous subarray of size k.

#include <vector>
#include <string>
#include <limits>
#include <iostream>
#include <queue>
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

using namespace std;

int findMax(const vector<int> numbers, int begin, int end) {
  int currentMax = -numeric_limits<int>::max();
  for (int i = begin; i < end; i++) {
    currentMax = max(currentMax, numbers[i]);
  }
  return currentMax;
}

vector<int> naiveSlidingMaximum(const vector<int> &numbers, int k) {
  vector<int> res;
  for (int i = 0; i <= numbers.size() - k; i++) {
    res.push_back(findMax(numbers, i, i+k));
  }
  return res;
}

vector<int> slidingMaximum(const vector<int> &numbers, int k) {
  // 1, 2, 3, 1, 1, 1, 4, 5, 2, 3, 6
  //                      i
  // q = {6:10, }
  vector<int> res;
  struct item {
    int value;
    int index;
    bool operator < (const item &rhs) const {
      return value < rhs.value;
    }
  };
  priority_queue<item> q;
  for (int i = 0; i < k; i++) {
    q.push({numbers[i], i});
  }
  for (int i = 0; i <= numbers.size() - k; i++) {
    // remove max elements of queue that do not belong to the target range anymore
    while (q.size() && q.top().index < i) {
      q.pop();
    }
    res.push_back(q.top().value);
    if (i + k < numbers.size()) {
      q.push({numbers[i+k], i+k});
    }
  }
  return res;
}

TEST_CASE("sliding-window-maximum-1") {
  auto arr = vector<int> {1, 2, 3, 1, 1, 1, 4, 5, 2, 3, 6};
  REQUIRE(naiveSlidingMaximum(arr, 3) == vector<int>({3, 3, 3, 1, 4, 5, 5, 5, 6}));
  REQUIRE(slidingMaximum(arr, 3) == vector<int>({3, 3, 3, 1, 4, 5, 5, 5, 6}));
}

TEST_CASE("sliding-window-maximum-2") {
  auto arr = vector<int> {8, 5, 10, 7, 9, 4, 15, 12, 90, 13};
  REQUIRE(naiveSlidingMaximum(arr, 4) == vector<int>({10, 10, 10, 15, 15, 90, 90}));
  REQUIRE(slidingMaximum(arr, 4) == vector<int>({10, 10, 10, 15, 15, 90, 90}));
}
