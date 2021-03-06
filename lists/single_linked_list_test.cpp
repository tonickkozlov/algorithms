#include <iostream>
#include <vector>
#include "single_linked_list.h"

using namespace std;

void testBasics() {
    SingleLinkedList list;
    list.PushBack(0);
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);
    cout << "size " <<  list.size() << "\n";
    list.print();

    list.PushFront(-1);
    list.PushFront(-2);
    list.PushFront(-3);
    cout << "size " <<  list.size() << "\n";
    list.print();

    while (list.size() > 0) {
        cout << list.PopFront() << " new size" << list.size() << "\n";
    }
    cout << list.PopFront() << "\n";
    list.PushBack(100);
    cout << list.PopFront() << "\n";
    cout << "List is empty and its size is " << list.size();
}

void testInsert() {
    SingleLinkedList list;
    list.Insert(0, 0);
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);

    list.Insert(0, 99); // insert after 0th position
    list.print(); // 0, 99, 1, 2, 3
    list.Insert(2, 100);
    list.print(); // 0, 99, 1, 100, 2, 3
    list.Insert(5, 101);
    list.print(); // 0, 99, 100, 1, 2, 3, 101
    cout << "size now is " << list.size() << endl;
}

void testReverse() {
    SingleLinkedList list;
    list.Insert(0, 0);
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);

    list.Reverse();
    list.print(); // 3, 2, 1, 0

    SingleLinkedList list2;
    list2.PushBack(1);
    list2.PushBack(2);
    list2.Reverse();
    list2.Insert(1, 3);
    list2.print(); // 2, 3, 1
}

void testIter() {
    SingleLinkedList list;
    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);
    SingleLinkedList::iterator iter = list.begin();
    SingleLinkedList::iterator end = list.end();

    for (auto v: list) {
        cout << v << " ";
    }
}

int main(int argc, char**) {

    testBasics();
    testInsert();
    testReverse();
    testIter();
    return 0;
}
