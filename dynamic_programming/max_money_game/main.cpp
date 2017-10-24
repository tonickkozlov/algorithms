#include <vector>
#include <iostream>

using namespace std;

int MaxMoneyMem(vector<int> coins, size_t begin, size_t end, vector<vector<int> > &mem) { // 0,3 //2,3
    cout << begin << " " << end << endl;
    if (mem[begin][end] == 0) {
        if(begin == end) {
            mem[begin][end] = coins[begin];
        } else if(end == begin+1) {
            mem[begin][end] = max(coins[begin], coins[end]);
        } else {
        mem[begin][end] = max(
                coins[begin] + min(
                    MaxMoneyMem(coins, begin+2, end, mem),
                    MaxMoneyMem(coins, begin+1, end-1, mem)
                    ),
                coins[end] + min(
                    MaxMoneyMem(coins, begin+1, end-1, mem),
                    MaxMoneyMem(coins, begin, end-2, mem)
                    )
                );
        }
    }
    return mem[begin][end];
}

int MaxMoney(vector<int> coins, size_t begin, size_t end) { // 0,3 //2,3
    static vector<vector<int> > mem(coins.size(), vector<int>( coins.size(), 0 ));
    if(begin == end) {
        return coins[begin];
    }
    if(end == begin+1) {
        return max(coins[begin], coins[end]);
    }
    return max(
            coins[begin] + min(
                MaxMoney(coins, begin+2, end),
                MaxMoney(coins, begin+1, end-1)
                ),
            coins[end] + min(
                MaxMoney(coins, begin+1, end-1),
                MaxMoney(coins, begin, end-2)
                )
            );
}

int MaxMoneyBU(vector<int> coins) { // 0,3 //2,3
    vector<vector<int> > mem(coins.size(), vector<int>( coins.size(), 0 ));
    for (int i = 0; i < coins.size(); i++) {
        mem[i][i] = coins[i];
    }
    for(int gap = 2; gap <= coins.size(); ++gap ) {
        for(int begin = 0; begin < coins.size()-gap+1; ++begin) {
            int end = begin + gap - 1;
            if(begin == end) {
                mem[begin][end] = coins[begin];
            } else if(end == begin+1) {
                mem[begin][end] = max(coins[begin], coins[end]);
            } else {
                mem[begin][end] = max(
                        coins[begin] + min(
                            mem[ begin+2][ end ],
                            mem[ begin+1][ end-1 ]
                            ),
                        coins[end] + min(
                            mem[ begin+1][ end-1 ],
                            mem[ begin][ end-2 ]
                            )
                        );
            }
        }
    }
    return mem[0][coins.size()-1];
}

vector<vector<int>> createMem(size_t size) {
    vector<vector<int> > mem(size, vector<int>( size, 0 ));
    return mem;
}

void printMem(vector<vector<int> > &mem) {
    for (const auto &v : mem) {
        for (const auto &e : v) {
            cout << e << " ";
        }
        cout << endl;
    }
}

int main() {
    cout << MaxMoneyBU(vector<int>{5, 3, 7, 10}) << endl;
    cout << MaxMoneyBU(vector<int>{8, 15, 3, 7}) << endl;
}
