// Sort a K-sorted array (each element is at most K steps away from it's position in a sorted array)

#include <vector>
#include <string>
#include <limits>
#include <iostream>
#include <queue>
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

using namespace std;
//             i             j
// {2, 6, 56, 12, 3, 8};
//  8, 12, 56
//  2, 3  6,
vector<int>& sortKSorted(vector<int> &kSorted, int k) {
  priority_queue<int, vector<int>, greater<int>> q;
  for (int i = 0; i < k+1; i++) {
    q.push(kSorted[i]);
  }
  for (int i = 0, j = k+1; i < kSorted.size(); i++, j++) {
    kSorted[i] = q.top(); q.pop();
    if (j < kSorted.size()) {
      q.push(kSorted[j]);
    }
  }
  return kSorted;
}

TEST_CASE("K-sorted array") {
  vector<int> kSorted = {2, 6, 56, 12, 3,  8};
  vector<int> sorted =  {2, 3, 6,  8,  12, 56};
  REQUIRE(sortKSorted(kSorted, 3) == sorted);
}
