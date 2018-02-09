// Find how many changes a string requires to become a palindrome

#include <vector>
#include <iostream>
#include <limits>

#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

using namespace std;
// finds max fifference between elements in an array where
// a minimal orrurs earlient than the maximal
long findMaximalDifference(const vector<int> &arr) {
  long maxDiff = 0;
  int start = 0;
  for (int i = 1; i < arr.size(); i++) {
    long currentDiff = static_cast<long>(arr[i]) - static_cast<long>(arr[start]);
    if (arr[i] > arr[start] && (currentDiff > maxDiff)) {
      maxDiff = currentDiff;
    }
    if (arr[i] < arr[start]) {
      start = i;
    }
  }
  return maxDiff;
}

void print(const vector<vector<int>> &q) {
  for (const auto &row: q) {
    for (const auto &el: row) {
      cout << el << " ";
    }
    cout << endl;
  }
}

void print(const vector<pair<int, int>> &v) {
  for (const auto &el: v) {
    cout << "(" << el.first << " " << el.second << ")";
  }
  cout << endl;
}

// turn stock prices into "candles" (pairs low-high)
vector<pair<int, int>> normalizePrices(vector<int> raw) {
  auto res = vector<pair<int, int>>();
  int start = 0, end = 0, i = 0;

  while (i < raw.size()) {
    start = i;
    while (start < raw.size() - 1 && raw[start] >= raw[start+1]) {
      start++;
    }
    end = start;
    while (end < raw.size()-1 && raw[end] <= raw[end+1]) {
      end++;
    }
    if (end > start) {
      res.emplace_back(raw[start], raw[end]);
    }
    i = end+1;
  }
  return res;
}

long findMaxProfit(const vector<pair<int, int>> &arr) {
  if (!arr.size()) {
    return 0;
  }
  auto dp = vector<vector<int>>(arr.size()+1, vector<int>(arr.size(), 0)); // x -> start of buys, y - end of buys

  // calc for subset pairs of len 1
  for (int i = 0; i < arr.size(); i++) {
    dp[1][i] = arr[i].second - arr[i].first;
  }

  // from len 2 to rest
  for (int len = 2; len <= arr.size(); len++) {
    for (int i = 0; i < arr.size()-len+1; i++) {
      dp[len][i] = max(arr[i+len-1].second - arr[i].first, dp[len-1][i] + arr[i+len-1].second - arr[i+len-1].first);
    }
  }
  return dp[arr.size()][0];
}

// find max profit from stock prices when can buy and sell only once
long findMaxProfit(const vector<int> &raw) {
  return findMaxProfit(normalizePrices(raw));
}

TEST_CASE("Max differnce") {
  int maxInt = numeric_limits<int>::max();
  REQUIRE(findMaximalDifference({20, 200, 210, 1000}) == 1000-20);
  REQUIRE(findMaximalDifference({20, 200, 0, -210, 0}) == 0-(-210));
  REQUIRE(findMaximalDifference({0, 50, -maxInt, maxInt}) == (static_cast<long>(maxInt) * 2));
  REQUIRE(findMaximalDifference({100, 180, 260, 310, 40, 535, 695}) == 695 - 40);
  REQUIRE(findMaximalDifference({10, 22, 5, 75, 65, 80}) == 80-5);
  REQUIRE(findMaximalDifference({20, 580, 420, 900}) == 900-20);
}

TEST_CASE("Max profit") {
  int maxInt = numeric_limits<int>::max();
  REQUIRE(findMaxProfit({20, 580, 420, 900}) == (580-20) + (900-420)); //1040
  REQUIRE(findMaxProfit({10, 22, 5, 75, 65, 80}) == (22-10)+(75-5)+(80-65)); // 97
  REQUIRE(findMaxProfit({{10, 75}, {30, 50}, {65, 80}}) == (75-10)+(50-30)+(80-65)); // 100
}
