// Given a set of activities defined as {{S0, F0}, ..., {Sn, Fn}}
// find a subset of compatible activities with maximal size

#include <vector>
#include <string>
#include <iostream>
#include <functional>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

#define CATCH_CONFIG_MAIN
#include "./catch.hpp"

using namespace std;

struct MyFile {
    MyFile() {
        cout << "file opened" << endl;
    }
    ~MyFile() {
        cout << "file closed" << endl;
    }
};

struct defer {
    defer(std::function<void()> a): action_(a) {};
    ~defer() {
        action_();
    }
private:
    std::function<void()> action_;
};

template<class T>
class Queue {
    queue<T> q_;
    mutex q_busy_;
    condition_variable q_empty_;

public:
    void push(const T& v) {
        unique_lock<mutex> lock(q_busy_);
        q_.push(v);
        q_empty_.notify_one();
    }

    T pop() {
        unique_lock<mutex> lock(q_busy_);
        while (q_.empty()) {
            q_empty_.wait(lock);
        }
        T front = q_.front(); q_.pop();
        return front;
    }
};

TEST_CASE( "Defer" ) {
    MyFile *f = new MyFile();
    defer([f](){ delete f; });
}

void consumer(Queue<int> *q) {
    for (int i = 0; i < 5; i++) {
        cout << q->pop() << " ";
    }
    cout << endl;
}

void producer(Queue<int> *q) {
    cout << "Waiting to begin producing" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << "Begin producing" << endl;
    for (int i = 0; i < 5; i++) {
        q->push(i);
        cout << "Produced " << i << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

TEST_CASE( "Threading" ) {
    Queue<int> q;
    thread producer_thread(producer, &q);
    thread consumer_thread(consumer, &q);
    producer_thread.join();
    consumer_thread.join();
}
