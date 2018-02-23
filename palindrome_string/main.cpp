// Find how many changes a string requires to become a palindrome

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

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
/* Finding if a string is a palindrome boils down to finding an edit distance
 between it's left and (flipped) right halves.
 */
int editDistance(string s1, string s2) {
  vector<vector<int>> q(s1.size()+1, vector<int>(s2.size()+1, 0));
  for (int i = 0; i < s1.size()+1; i++) {
    q[i][0] = i;
  }
  for (int j = 0; j < s2.size()+1; j++) {
    q[0][j] = j;
  }
  for (int i = 1; i <= s1.size(); i++) {
    for (int j = 1; j <= s2.size(); j++) {
      if (s1[i-1] == s2[j-1]) {
        q[i][j] = q[i-1][j-1];
      } else {
        q[i][j] = 1 + min(min(q[i-1][j], q[i][j-1]), q[i-1][j-1]);
      }
    }
  }
  return q[s1.size()][s2.size()];
}

int palindromeDistance(string s) {
  string s1, s2;
  s1 = s.substr(0, s.size() / 2);
  if (s.size() % 2 == 0) {
    s2 = s.substr(s.size() /2);
  } else {
    s2 = s.substr(s.size() / 2 + 1);
  }
  reverse(s2.begin(), s2.end());
  return editDistance(s1, s2);
}

TEST_CASE( "Edit distance" ) {
  REQUIRE(editDistance("abcd", "acd") == 1);
  REQUIRE(editDistance("bbbb", "cccc") == 4);
  REQUIRE(editDistance("banana", "ananas") == 2);
  REQUIRE(editDistance("a", "ananas") == 5);
  REQUIRE(editDistance("saturday", "sunday") == 3);

  REQUIRE(palindromeDistance("ananas") == 2);
  REQUIRE(palindromeDistance("abccdba") == 1);
}
