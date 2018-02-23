// Find the length of the longest palindromic subsequence in a string

#include <vector>
#include <string>
#include <iostream>
\
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

using namespace std;

void print(const vector<vector<int>> &q) {
  for (const auto &row: q) {
    for (const auto &el: row) {
      cout << el << " ";
    }
    cout << endl;
  }
}

string longestPalindromicSubsequence(string s) {
  vector<vector<int>> q(s.size(), vector<int>(s.size(), 0));
  int maxLength = 1;
  for (int i = 0; i < s.size(); i++) {
    q[i][i] = 1;
  }
  int start = 0;
  for (int i = 0; i < s.size()-1; i++) {
    if (s[i] == s[i+1]) {
      start = i;
      maxLength = 2;
      q[i][i+1] = 1;
    }
  }
  for (int k = 3; k <= s.size(); k++) {
    for (int i = 0; i < s.size()-k+1; i++) {
      int j = i + k - 1;
      if (q[i+1][j-1] == 1 && s[i] == s[j]) {
        q[i][j] = 1;
        if (k > maxLength) {
          maxLength = k;
          start = i;
        }
      }
    }
  }
  print(q);

  return s.substr(start, maxLength);
}

TEST_CASE( "Edit distance" ) {
  REQUIRE(longestPalindromicSubsequence("forgeeksskeegfor") == "geeksskeeg");
  REQUIRE(longestPalindromicSubsequence("forgeeksbskeegfor") == "geeksbskeeg");

}
