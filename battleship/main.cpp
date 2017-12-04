// Given a set of activities defined as {{S0, F0}, ..., {Sn, Fn}}
// find a subset of compatible activities with maximal size

#include <vector>

#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

using namespace std;

vector<pair<int, int>> findShip(const vector<vector<int>> battlefield, int shipSize = 3) {
    vector<pair<int, int>> result;
    pair<int, int> firstCell;
    for (int i = 0; i < battlefield.size(); i++) {
        bool bFound = false;
        for (int j = 0; j < battlefield[0].size(); j++) {
            if (battlefield[i][j] == 1) {
                firstCell = {i, j};
                bFound = true;
                break;
            }
        }
        if (bFound) {
            break;
        }
    }
    // firstCell - cell containing a ship
    result.push_back(firstCell);
    for (int i = 1; i < shipSize; i++) {
        if (battlefield[firstCell.first + i][firstCell.second] == 1) {
            result.emplace_back(firstCell.first + i, firstCell.second);
        } else if (battlefield[firstCell.first][firstCell.second + i] == 1) {
            result.emplace_back(firstCell.first, firstCell.second + i);
        }
    }

    return result;
}

void print(const vector<vector<int>> &field) {
    for (const auto &row: field) {
        for (const auto &item: row) {
            cout << item << " ";
        }
        cout << endl;
    }
}

TEST_CASE("Finding a ship") {
    vector<vector<int>> battlefield(5, vector<int>(5, 0));
    battlefield[1][1] = 1;
    battlefield[1][2] = 1;
    battlefield[1][3] = 1;
    print(battlefield);
    auto coordinates = findShip(battlefield);
    auto expected = vector<pair<int, int>> {{1, 1}, {1, 2}, {1, 3}};
    REQUIRE(coordinates == expected);
}
