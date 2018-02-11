// Implements Rabin-Karp's pattern matching algorithm

#include <vector>
#include <string>
#include <limits>
#include <iostream>
#include <queue>
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

using namespace std;

vector<int> RabinKarp(const string &txt, const string &pattern, int prime = 101 /*prime number for hashing */) {
  int d = 256; // number of characters in alphabet
  vector<int> matches;
  int txt_hash = 0;
  int pattern_hash = 0;
  int h = 1; // value for pattern's highest digit, == pow(d, pattern.size()-1) % prime

  for (int i = 0; i < pattern.size() - 1; i++) {
    h = (h * d) % prime;
  }

  // calc hashes for the first window of PATTERN
  for (int i = 0; i < pattern.size(); i++) {
    pattern_hash = (pattern_hash * d + pattern[i]) % prime;
    txt_hash = (txt_hash * d + pattern[i]) % prime;
  }

  for (int i = 0; i <= txt.size() - pattern.size(); i++) {
    if (pattern_hash == txt_hash) {
      if (pattern == txt.substr(i, pattern.size())) {
        matches.push_back(i);
      }
    }

    if (i < txt.size() - pattern.size()) {
      txt_hash = (d * (txt_hash - txt[i] * h) + txt[i+pattern.size()]) % prime;
    }
    if (txt_hash < 0) {
      txt_hash += prime;
    }
  }
  return matches;
}

TEST_CASE("sliding-window-maximum-1") {
  auto expected = vector<int>{0, 10};
  REQUIRE(RabinKarp("geeks for geeks", "geek") == expected);
}
