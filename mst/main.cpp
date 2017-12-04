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

char get_min_key(const map<char, int> &keys, const set<char> &visited) {
    char min_key = '\0';
    int min_value = std::numeric_limits<int>::max();
    for (const auto &kv: keys) {
        char key = kv.first;
        int value = kv.second;
        if (visited.count(key) == 0 && (value < min_value)) {
            min_key = key;
            min_value = value;
        }
    }
    return min_key;

}
map<char, char> Mst(Graph &graph, char start) {
    set<char> visited;
    map<char, int> keys;
    for (const auto &kv: graph) {
        keys[kv.first] = numeric_limits<int>::max();
    }
    keys[start] = 0;
    map<char, char> parents;
    parents[start] = '\0';

    for (int i = 0; i < graph.size(); i++) {
        char min_key = get_min_key(keys, visited);
        visited.insert(min_key);
        for (const auto &edge: graph[min_key]) {
            if ((visited.count(edge.dst) == 0) && (edge.weight < keys[edge.dst])) {
                keys[edge.dst] = edge.weight;
                parents[edge.dst] = min_key;
            }
        }
    }
    return parents;
}

TEST_CASE( "Prim's MST" ) {
    Graph graph = {
        {'a', {{'b', 3}, {'c', 8}} },
        {'b', {{'a', 3}, {'d', 1}, {'c', 4}} },
        {'c', {{'a', 8}, {'b', 4}, {'d', 2}} },
        {'d', {{'b', 1}, {'c', 2}} },
    };

    map<char, char> parents = Mst(graph, 'a'); // for every node, show it's MST parent
    REQUIRE(parents['a'] == '\0');
    REQUIRE(parents['b'] == 'a');
    REQUIRE(parents['d'] == 'b');
    REQUIRE(parents['c'] == 'd');
}
