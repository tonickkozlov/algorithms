// Let S(n) be a sum of all digits of a number.
// Let a number n be complex if, for n does not exist a natural k that follows:
// n = 3*k/(S(k)^2)
// find first complex number

#include <vector>
#include <string>
#include <limits>
#include <iostream>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../catch.hpp"

using namespace std;

void permutations(string s, ostream &os=cout, int count=0) {
    if (count == s.size() - 1) {
        os  << s << endl;
    }
    for (int i = count; i < s.size(); i++) {
        swap(s[count], s[i]);
        permutations(s, os, count+1);
        swap(s[count], s[i]);
    }
}

TEST_CASE("PERMUTATIONS") {
    stringstream ss;
    permutations("ABC", ss);
    REQUIRE(ss.str() == "ABC\nACB\nBAC\nBCA\nCBA\nCAB\n");

    permutations("AA");
}
