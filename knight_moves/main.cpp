/**
 * Find if there's a solution to "Knight Tour" problem - to determine if a chess
 * knight can traverse the whole board without stepping on the same cell twice.
 */
#include <vector>
#include <string>
#include <map>

#include <iostream>
#include <array>
#include <queue>
#include <limits>
#include <unordered_set>

using namespace std;

const int SIZE = 6;
using field = array<int, 2>;

ostream &operator << (ostream &os, const field &f) {
    os << f[0] << f[1];
    return os;
}

field operator + (const field &f1, const field &f2) {
    return field{f1[0] + f2[0], f1[1] + f2[1]};
}

bool isValid(const field &f) {
    return (f[0] >= 0) && (f[0] < SIZE) && (f[1] >= 0) && (f[1] < SIZE);
}

struct field_hash {
    inline std::size_t operator()(const field &v) const {
        return v[0]*31 + v[1];
    }
};

vector<field> neighbours(const field &f) {
    vector<field> neighbours{};
    for (auto seed: {field{2, 1}, field{1, 2}}) {
        for (auto i: {1, -1}) {
            for (auto j: {1, -1}) {
                field neighbour = f + field{seed[0] * i, seed[1] * j};
                if (isValid(neighbour)) {
                    neighbours.push_back(neighbour);
                }
            }
        }
    }
    return neighbours;
}

bool knightMove(field currentPosition, unordered_set<field, field_hash> &movesMade, vector<field> &performedMoves) {
    movesMade.insert(currentPosition);
    printf("\33[2K\r"); cout << movesMade.size();
    performedMoves.push_back(currentPosition);
    for (const auto &m: performedMoves) {
        cout << m;
    }
    if (movesMade.size() == (SIZE*SIZE)) {
        return true;
    }
    for (const auto &n: neighbours(currentPosition)) {
        if (movesMade.count(n) == 0 && knightMove(n, movesMade, performedMoves)) {
            return true;
        }
    }
    movesMade.erase(currentPosition);
    performedMoves.pop_back();
    return false;
}

int main() {
    vector<field> performedMoves;
    unordered_set<field, field_hash> movesMade;
    if (knightMove(field{0, 0}, movesMade, performedMoves)) {
        cout << "Found !";
    }
    return 0;
}
