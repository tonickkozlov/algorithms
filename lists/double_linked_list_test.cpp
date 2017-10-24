#include <iostream>
#include <vector>
#include "double_linked_list.h"

using namespace std;

void testBasics() {
    DoubleLinkedList list;

    list.PushFront(-1);
    list.PushFront(-2);
    list.PushFront(-3);
    list.Print(); // -3<>-2<>-1

    list.PushBack(0);
    list.PushBack(1);
    list.Print(); // -3<>-2<>-1<>0<>1

    auto iter = list.begin();
    std::advance(iter, 2);
    cout << "Advanced" << *iter << endl;
    list.Insert(iter, 99);
    cout << "After insert" << endl;
    list.Print(); // -3<>-2<>-1<>99<>0<>1

    list.DeleteHead();
    cout << "After removed head" << endl;
    list.Print(); // -2<>-1<>99<>0<>1
}


int main(int argc, char**) {

    testBasics();
    return 0;
}
