// Matrix chain multiplication optimisation problem
// http://www.geeksforgeeks.org/dynamic-programming-set-8-matrix-chain-multiplication/

#include <vector>
#include <string>
#include <limits>
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

using namespace std;
struct Mat {
    int rows;
    int cols;
};

ostream& operator << (ostream &s, const Mat &m) {
    s << "(" << m.rows << " " << m.cols << ")";
    return s;
}

//     vector<Mat> v = {{10, 100}, {100, 5}, {5, 50}};
//                      bi                              e =  10*100*50 +
                                    //b                 e    10*5*50
                        //b           i                 e = 10 * 5 * 50 +
            //            b           e 100 * 5 * 50
//
int matrixChainMultRecur(const vector<Mat> &matrices, int begin, int end, int level=0) {
    cout << string(level, '\t') << "begin: " << begin << " " << "end: " << end;
    for (int i = begin; i < end; i++) {
        cout << matrices[i] << " ";
    }
    cout << endl;
    int q = 9999999;
    if (end-begin < 2) {
        q = 0;
    } else {
        for (int i = begin+1; i < end; i++) {
            int current = matrices[begin].rows * matrices[i-1].cols * matrices[end-1].cols;
            cout << string(level, '\t') << "i: " << i << " current " << current << endl;
            q = min(q, current +
                matrixChainMultRecur(matrices, begin, i, level+1) +
                matrixChainMultRecur(matrices, i, end, level+1));
        }
    }
    cout << string(level, '\t') << q << endl;
    return q;
}


int matrixChainMultNaive(const vector<Mat> &matrices) {
    return matrixChainMultRecur(matrices, 0, matrices.size());
}

void print(const vector<vector<int>> q) {
    for (auto row: q) {
        for (auto col: row) {
            cout << col << " ";
        }
        cout << endl;
    }
}

void print(const map<pair<int, int>, int> q) {
    for (auto &kv: q) {
        cout << "(" << kv.first.first << ", " << kv.first.second << "): " << kv.second << endl;
    }
}

int matrixChainMultDyn(const vector<Mat> &matrices) {
    map<pair<int, int>, int> q;
    // fill in for every pair of matrix and for empty cases
    for (int sz = 0; sz < 2; ++sz) {
        for (int i = 0; i <= matrices.size() - sz; ++i) {
            q[make_pair(i, i+sz)] = 0;
        }
    }
    for (int sz = 2; sz <= matrices.size(); sz++) {
        for(int i = 0; i <= matrices.size() - sz; i++) {
            pair<int, int> target = make_pair(i, i + sz);
            q[target] = numeric_limits<int>::max();

            for (int j = target.first+1; j < target.second; j++) {
                int current = matrices[target.first].rows * matrices[j-1].cols * matrices[target.second-1].cols
                 + q[make_pair(target.first, j)]
                 + q[make_pair(j, target.second)];
                q[target] = min(q[target], current);
            }
        }
    }
    return q[make_pair(0, matrices.size())];
}
TEST_CASE( "Can solve with simple recursion ") {
    REQUIRE(matrixChainMultNaive({{10, 100}, {100, 5}, {5, 50}}) == 7500);
    REQUIRE(matrixChainMultNaive({{5, 50}, {50, 100}, {100, 1}, {1, 10}}) == 5300);
}

TEST_CASE( "Can solve with dp ") {
    REQUIRE(matrixChainMultDyn({{10, 100}, {100, 5}, {5, 50}}) == 7500);
    REQUIRE(matrixChainMultDyn({{5, 50}, {50, 100}, {100, 1}, {1, 10}}) == 5300);
}
