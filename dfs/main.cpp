// Given a set of activities defined as {{S0, F0}, ..., {Sn, Fn}}
// find a subset of compatible activities with maximal size

#include <vector>
#include <string>
#include <iostream>

#include "./dfs.h"
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

using namespace std;
void print(const map<char, int> m) {
    for (const auto &kv: m) {
        cout << kv.first << ": " << kv.second << endl;
    }
}

TEST_CASE( "BFS" ) {
    string s = "hello";
    map<char, edge_list> edges = {
        {'a', {'b'}},
        {'b', {'c', 'd'}},
        {'c', {}},
        {'d', {'a'}},
    };

    map<char, int> discoveries, finishes;
    map<char, char> parents;
    DFS(edges, 'a', &discoveries, &finishes);
    map<char, int> expectedDiscoveries = {
        {'a', 0},
        {'b', 1},
        {'c', 2},
        {'d', 4}
    };
    map<char, int> expectedFinishes = {
        {'a', 7},
        {'b', 6},
        {'c', 3},
        {'d', 5}
    };
    print(discoveries);
    REQUIRE(discoveries == expectedDiscoveries);
    REQUIRE(finishes == expectedFinishes);
    vector<pair<char, int>> finishedPairs(finishes.begin(), finishes.end());
    sort(finishedPairs.begin(), finishedPairs.end(), [](const pair<char, int> &kv1, const pair<char, int> &kv2) {return kv1.second > kv2.second;});
    string topoSort;
    for (const auto &kv: finishedPairs) {
        topoSort += kv.first;
    }
    REQUIRE(topoSort == "abdc");
}
