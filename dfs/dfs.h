#ifndef _DFS_H
#define _DFS_H

#include <vector>
#include <map>
#include <stack>

using edge_list = std::vector<char>;

/*
adj:
    a -> b
    b -> c, d
    c -> {},
    d -> a
st: a b

bFin = f
t = 7
fin: {
    c: 3
    d: 5
    b: 6
    a: 7
}
dis: {
    a: 0,
    b: 1
    c: 2
    d: 4
}
par: {

}
*/
void DFS(std::map<char, edge_list> edges, char start,
    std::map<char, int> *out_discoveries = nullptr,
    std::map<char, int> *out_finishes = nullptr,
    std::map<char, char> *out_parents = nullptr
) {
    using namespace std;
    // discovery times, finish times
    map<char, int> discoveries, finishes;
    discoveries[start] = 0;
    stack<char> st;
    st.push(start);
    int tick = 1;
    for (; !st.empty();) {
        bool bFinished = true; // finished current vertex's adj list traversal

        char current = st.top();
        for (char v: edges[current]) {
            if (discoveries.find(v) == discoveries.end()) {
                if (out_parents) {
                    (*out_parents)[v] = current;
                }
                discoveries[v] = tick; tick++;
                bFinished = false;
                st.push(v);
                break;
            }
        }
        if (bFinished) {
            finishes[current] = tick; tick++;
            st.pop();
       }
    }
    if (out_discoveries) {
        *out_discoveries = discoveries;
    }
    if (out_finishes) {
        *out_finishes = finishes;
    }
}

#endif
