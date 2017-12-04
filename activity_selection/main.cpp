// Given a set of activities defined as {{S0, F0}, ..., {Sn, Fn}}
// find a subset of compatible activities with maximal size

#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <random>
#include <chrono>
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

using namespace std;

using activity = pair<int, int>;

ostream& operator << (ostream& out, const activity& a) {
    out << "[" << a.first << " " << a.second << "]";
    return out;
}

// a =   {{1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 9}, {5, 9}, {6, 10}, {8, 11}, {8, 12}, {2, 14}, {12, 16}};
//                                                                                             l            i
// res =    {{1, 4}, {5, 7}, {8, 11}, {12, 16}}
// wasPicked = true
// lastPickedActivity = 0
vector<activity> optimize(vector<activity> &activities) {
    // sort activities by finish time
    if (activities.size() == 0) {
        return vector<activity> {};
    }
    sort(activities.begin(), activities.end(), [](const activity &a1, const activity &a2) { return a1.second < a2.second; });
    vector<activity> result {activities[0]};
    int lastPickedActivity = 0;
    bool wasPicked;
    do {
        wasPicked = false; // an activity was picked on this run
        for (int i = lastPickedActivity+1; i < activities.size(); i++) {
            if (activities[i].first >= activities[lastPickedActivity].second) {
                result.push_back(activities[i]);
                lastPickedActivity = i;
                wasPicked = true;
                break;
            }
        }
    } while(wasPicked);
    return result;
}

TEST_CASE( "Greedy activity selection" ) {
    vector<activity> activities {{1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 9}, {5, 9}, {6, 10}, {8, 11}, {8, 12}, {2, 14}, {12, 16}};
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(activities.begin(), activities.end(), default_random_engine(seed));
    REQUIRE(optimize(activities) == vector<activity>({{1, 4}, {5, 7}, {8, 11}, {12, 16}}));
}
