// Let S(n) be a sum of all digits of a number.
// Let a number n be complex if, for n does not exist a natural k that follows:
// n = 3*k/(S(k)^2)
// find first complex number

#include <vector>
#include <string>
#include <limits>
#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../catch.hpp"

using namespace std;
int sumOfDigits(int n) {
    int result = 0;
    while (n) {
        result += n % 10;
        n /= 10;
    }
    return result;
}

double formula(double k) {
    return 3.0 * double(k) / pow(sumOfDigits(k), 2);
}

bool isWhole(double x) {
    return x == int(x);
}

int findComplexNumber() {
    set<int> naturals;
    const int SIZE = 10000;
    for (int k = 1; k < SIZE; k++) {
        double n = formula(double(k));
        if (isWhole(n)) {
            naturals.insert(int(n));
        }
    }

    for (int n = 1; n < SIZE; n++) {
        if (naturals.find(n) == naturals.end()) {
            return n;
        }
    }
    return -1;

}

TEST_CASE("Sum of digits") {
    REQUIRE(sumOfDigits(10) == 1);
    REQUIRE(sumOfDigits(123) == 1 + 2 + 3);
}

TEST_CASE("Formula") {
    REQUIRE(formula(10) == 30);
    REQUIRE(formula(12) == 4);
    REQUIRE(formula(13) == 2.4375);
    // cout << findComplexNumber() << endl;
}

TEST_CASE("IsWhole") {
    REQUIRE(isWhole(2.0) == true);
    REQUIRE(isWhole(2.5) == false);
}

TEST_CASE("Final") {
    cout << findComplexNumber() << endl;
}
