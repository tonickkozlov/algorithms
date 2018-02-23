/**
 * Create a MedialCalculator class that would return a median for every number passed to it
 * e.g.
 * auto c = MedianCalculator()
 * c.put(1)
 * > 1
 * c.put(3)
 * > 2
 * c.put(5)
 * > 3
 */
#include <vector>
#include <queue>

#include <iostream>
#include <limits>

#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

using namespace std;

class IMedianCalculator {
public:
    virtual float put(int) = 0;
    virtual ~IMedianCalculator() {};
};

class NaiveMedianCaluculator: public IMedianCalculator {
public:
    float put(int x) override {
        numbers_.push_back(x);
        sort(numbers_.begin(), numbers_.end());
        if (numbers_.size() % 2 == 1) {
            return numbers_[numbers_.size() / 2];
        } else {
            return float(numbers_[numbers_.size() / 2 - 1] + numbers_[numbers_.size() / 2]) / 2;
        }
    }
private:
    vector<int> numbers_;
};

class HeapMedianCalculator: public IMedianCalculator {
public:
    float put(int x) override {
        if (x > currentMedian_) {
            if (max_.size() == min_.size()) {
                min_.push(max_.top());
                max_.pop();
            }
            max_.push(x);
        }
        else {
            if (min_.size() > max_.size()) {
                max_.push(min_.top());
                min_.pop();
            }
            min_.push(x);
        }
        if (max_.size() == min_.size()) {
            currentMedian_ = float(min_.top() + max_.top()) / 2;
        } else {
            currentMedian_ = min_.top();
        }
        return currentMedian_;
    }
    private:
        priority_queue<int, std::vector<int>, std::greater<int>> max_;               // highest half
        priority_queue<int> min_; // lowest half
        float currentMedian_ = std::numeric_limits<float>::max();
};

void test_calc(IMedianCalculator *calc) {
    REQUIRE(calc->put(0) == 0);
    REQUIRE(calc->put(1) == 0.5);
    REQUIRE(calc->put(5) == 1);
    REQUIRE(calc->put(4) == 2.5);
    REQUIRE(calc->put(100) == 4);
    REQUIRE(calc->put(-1) == 2.5);
    REQUIRE(calc->put(1) == 1);
}

TEST_CASE("Increasing seq") {
    IMedianCalculator *calc1 = new NaiveMedianCaluculator();
    IMedianCalculator *calc2 = new HeapMedianCalculator();
    // test_calc(calc1);
    test_calc(calc2);
    delete calc1;
    delete calc2;
}
