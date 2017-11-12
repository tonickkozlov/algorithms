// Longest common substring problem (do not confues with longest common subsequence which )
// does not require a subsequence to be consequitive

#include <vector>
#include <string>
#include <limits>
#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

using namespace std;

// aaaafooaaa 0
//     ^  ^
// bfoob 0
//     ^
pair<int, int> RecurseLCS(const string &s1, const string &s2, int begin1, int begin2, int level=0, vector<vector<int>> *mem=nullptr) {
    // max number of characters matching between s1 starting at begin1, and s2, starting from begin2
    pair<int, int> res;
    if (begin1 >= s1.size() || begin2 >= s2.size()) {
        res = make_pair(begin1, 0);
    } else {
        int currentLength = 0;
        for (int b1=begin1, b2=begin2; b1<s1.size() && b2<s2.size() && s1[b1] == s2[b2]; b1++, b2++) {
            currentLength++;
        }
        pair<int, int> res1 = RecurseLCS(s1, s2, begin1+1, begin2, level+1, mem);
        pair<int, int> res2 = RecurseLCS(s1, s2, begin1, begin2+1, level+1, mem);
        if (currentLength > res1.second || currentLength > res2.second) {
            res = make_pair(begin1, currentLength);
        } else {
            res = res1.second > res2.second ? res1 : res2;
        }
    }
    (*mem)[begin1][begin2] = res.second;
    return res;
}

void print(const vector<vector<int>> x, const string &s1, const string &s2) {
    cout << "  | ";
    for (int i = 0; i < x[0].size(); i++) {
        cout << s2[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < x.size(); i++) {
        cout << s1[i] << " | ";
        for (const auto &v: x[i]) {
            cout << v << " ";
        }
        cout << endl;
    }
}

string NaiiveLCS(const string &s1, const string &s2) {
    vector<vector<int>> mem (s1.size() +1, vector<int>(s2.size() + 1, 0));
    pair<int, int> res = RecurseLCS(s1, s2, 0, 0, 0, &mem);
    print(mem, s1, s2);
    return s1.substr(res.first, res.second);
}

string DynamicLCS(const string &s1, const string &s2) {
    vector<vector<int>> r(s1.size() + 1, vector<int>(s2.size() + 1, 0));
    for(int i = s1.size()-1; i >= 0; --i) {
        for (int j = s2.size()-1; j >= 0; --j) {
            for (int b1=i, b2=j; b1<=s1.size() && b2<=s2.size() && s1[b1] == s2[b2]; b1++, b2++) {
                r[i][j] += 1;
            }
            r[i][j] = max(r[i][j], max(r[i][j+1], r[i+1][j]));
        }
    }
    print(r, s1, s2);
    int LcsSize = r[0][0];
    // let's find beginning of the LCS in 1st string and return it
    int LcsBegin = 0;
    while (r[LcsBegin+1][0] == LcsSize) {
        LcsBegin++;
    }
    return s1.substr(LcsBegin, LcsSize);
}

TEST_CASE("Naiive LCS") {
    REQUIRE(NaiiveLCS("aaaafooaaa", "bfoob") == "foo");
    REQUIRE(NaiiveLCS("aaafoooaafooa", "bfobfoobfooob") == "fooo");
    REQUIRE(NaiiveLCS("afoafooa", "bfobfoob") == "foo");
}

TEST_CASE("Dynamic LCS") {
    REQUIRE(DynamicLCS("aaaafooaaa", "bfoob") == "foo");
    REQUIRE(DynamicLCS("aaadoooaafooa", "bfobfoobdooob") == "dooo");
    REQUIRE(DynamicLCS("afoafooa", "bfobfoob") == "foo");
}
