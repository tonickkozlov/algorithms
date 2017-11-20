#ifndef _BFS_H
#define _BFS_H

#include <vector>
#include <map>
#include <queue>
#include <set>

using edge_list = std::vector<char>;

std::map<char, int> BFS(std::map<char, edge_list> edges, char start, std::map<char, char> *parents = nullptr) {
    using namespace std;
    map<char, int> bfs;
    set<char> visited;
    queue<pair<char, int>> q;

    q.emplace(start, 0);
    visited.insert(start);
    while (!q.empty()) {
        pair<char, int> current = q.front();q.pop();
        bfs.insert(current);

        for (char v: edges[current.first]) {
            if (visited.find(v) == visited.end()) {
                q.emplace(v, current.second + 1);
                visited.insert(v);
                if (parents) {
                    (*parents)[v] = current.first;
                }
            }
        }
    }
    return bfs;
}

#endif
