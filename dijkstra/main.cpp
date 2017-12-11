// Given a set of activities defined as {{S0, F0}, ..., {Sn, Fn}}
// find a subset of compatible activities with maximal size

#include <vector>
#include <string>
#include <map>

#include <queue>
#include <limits>
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

using namespace std;
struct Edge {
    char dst;
    int weight;
};

using Graph = map<char, vector<Edge>>;

void print(const Graph &graph) {
    for (const auto &kv: graph) {
        for (const auto &v: kv.second) {
            cout << kv.first << " -> " << v.dst << "," << v.weight << "\n";
        }
    }
}

char find_min(const Graph &graph, map<char, int> &weights, set<char> &visited) {
    auto minWeight = numeric_limits<int>::max();
    auto minValue = '\0';
    for (const auto &kv: graph) {
        auto current = kv.first;
        if (visited.count(current) == 0 && weights[current] < minWeight) {
            minWeight = weights[current];
            minValue = current;
        }
    }
    return minValue;
}

map<char, int> dijkstra(Graph &graph, char start) {
    map<char, int> weights;
    set<char> visited;
    for (const auto &kv: graph) {
        weights[kv.first] = numeric_limits<int>::max();
    }
    weights[start] = 0;
    for (int i = 0; i < graph.size(); i++) {
        auto u = find_min(graph, weights, visited);
        visited.insert(u);
        for (const auto &v: graph[u]) {
            weights[v.dst] = min(weights[v.dst], weights[u] + v.weight);
        }
    }
    return weights;
}

TEST_CASE( "Dijkstra" ) {
    Graph graph = {
        {'a', {{'b', 3}, {'c', 8}} },
        {'b', {{'a', 3}, {'d', 1}, {'c', 4}} },
        {'c', {{'d', 2}} },
        {'d', {{'b', 1}, {'c', 2}} },
    };

    map<char, int> weights = dijkstra(graph, 'a');
    REQUIRE(weights['a'] == 0);
    REQUIRE(weights['b'] == 3);
    REQUIRE(weights['c'] == 6);
    REQUIRE(weights['d'] == 4);
}
