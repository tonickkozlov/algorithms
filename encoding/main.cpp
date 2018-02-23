/**
    Given a string (e.g.) "dfabcdfef", and an array of "codes"
    (e.g.) ["abc", "df", "ef"] (meaning that "abc" maps to 'a',
    "df" maps to 'b', "ef" maps to 'c'),
    find an encoded string
    "dfabcdfef" -> "babc"
    **/
#include <vector>
#include <string>
#include <map>

#include <limits>
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
using namespace std;

string encode(string s, vector<string> encodings) {
    map<string, char> dictionary;
    string res;
    for (int i = 0; i < encodings.size(); i++) {
        dictionary[encodings[i]] = ('a'+i);
    }

    int i = 0;
    while (i < s.size()) {
        bool bFound = false;
        int j = i+1;
        while (j <= s.size()) {
            string current = s.substr(i, j-i);
            if (dictionary.find(current) != dictionary.end()) {
                res += dictionary[current];
                bFound = true;
                break;
            }
            j++;
        }
        if (!bFound) {
            return "";
        }
        i = j;
    }
    return res;
}
TEST_CASE( "Encoding" ) {
    /*
    {"abc" -> "a"},
    {"df", "b"},
    {"ef", "c"}

    "dfabcdfef" -> "babc"
    */
    REQUIRE(encode("dfabcdfef", {"abc", "df", "ef"}) == "babc");
}
