/**
* Write a function that finds if input matches a given pattern, e.g.
* "redbluebluered" matches "abba" (a->red, b->blue),
* while "redbluered" does not match "abba"
*/

#include <vector>
#include <iostream>
#include <string>
#include <map>

#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

using namespace std;
string remove(string pattern, string c) {
    size_t found;
    while ((pattern.size() > 0 && c.size() > 0) && (found = pattern.find(c)) != string::npos) {
        pattern.erase(found, c.size());
    }
    return pattern;
}

// break input into words while there's still characters left in pattern
bool break_words(string input, string pattern, map<char, string> *dictionary, int depth=0) {
    // cout << string(depth, '\t') << "(" << input << ")" << " (" << pattern << ") " << endl;
    if (input.size() == 0 && pattern.size() == 0) {
        return true;
    } else if (input.size() == 0 || pattern.size() == 0) {
        return false;
    }
    for (int i = 1; i < input.size(); i++) {
        string current_substr = input.substr(0, i);

        string next_input = remove(input, current_substr);
        string next_pattern = remove(pattern, string(1, pattern[0]));
        if (break_words(next_input, next_pattern, dictionary, depth+1) == 1) {
            (*dictionary)[pattern[0]] = current_substr;
            return true;
        }
    }
    return 0;
}

bool can_match(string input, string pattern) {
    map<char, string> dictionary;
    break_words(input, pattern, &dictionary);
    // at this point, dictionary contains a map
    // (char -> word) that the pattern has been broken into.
    // build the new phrase based on pattern and dictionary to
    // see if it mathes the original pattern
    string fromPattern = "";
    for (char c : pattern) {
        fromPattern += dictionary[c];
    }
    return input == fromPattern;
}


TEST_CASE( "Correct match") {
    REQUIRE( can_match("redbluebluered", "abba") == true );
}

TEST_CASE( "Incorrect match") {
    REQUIRE( can_match("redbluered", "abab") == false );
}
