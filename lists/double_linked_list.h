#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include <iostream>
class DoubleLinkedList {
public:
    class node {
    public:
        node(int v): value(v), next(nullptr), prev(nullptr) {}
        int value;
        node *next;
        node *prev;
    private:
        node();
    };

    class iterator: public std::iterator<std::bidirectional_iterator_tag, int> {
        friend class DoubleLinkedList;
    public:
        iterator(node *c): it_(c) {}
        iterator& operator++ () {
            it_ = it_->next;
            return *this;
        }
        iterator& operator-- () {
            it_ = it_->prev;
            return *this;
        }
        void operator = (iterator &rhs) {
            it_ = rhs.it_;
        }

        int operator*() const {
            return it_->value;
        }

        bool operator == (const iterator &rhs) {
            return it_ == rhs.it_;
        }

        bool operator != (const iterator &rhs) {
            return !(*this == rhs);
        }

    private:
        node *it_;
    };


    DoubleLinkedList(): head_(nullptr), tail_(nullptr), size_(0) {}
    void PushFront(int val) {
        if (!head_) {
            head_ = new node(val);
            tail_ = head_;
        } else {
            node *oldHead = head_;
            head_ = new node(val);
            head_->next = oldHead;
            oldHead->prev = head_;
        }
        ++size_;
    }

    void PushBack(int val) {
        if (!head_) {
            return PushFront(val);
        }
        node *newTail = new node(val);
        newTail->prev = tail_;
        tail_->next = newTail;
        tail_ = newTail;
        ++size_;
    }

    iterator begin() const {
        return iterator(head_);
    }

    iterator rbegin() const {
        return iterator(tail_);
    }

    iterator end() const {
        return iterator(nullptr);
    }

    int size() const {
        return size_;
    }

    void DeleteHead() {
        if (!head_) {
            return;
        }
        node *toDelete = head_;
        std::cout << "removing head " << head_->value << std::endl;
        head_ = head_->next;
        if (head_) {
            head_->prev = nullptr;
        }

        --size_;
        delete toDelete;
    }

    void Insert(const iterator &before, int value) {
        node *newNode = new node(value);
        iterator after = ++(iterator(before));
        before.it_->next = newNode;
        newNode->prev = before.it_;
        newNode->next = after.it_;
        after.it_->prev = newNode;
    }

    void Print() const {
        std::cout << "size: " << size() << std::endl;
        std::cout << "fw: ";
        for (auto v:(*this)) {
            std::cout << v << " ";
            std::cout << std::endl;
        }

        std::cout << "bw: ";
        for (auto it = rbegin(); it != end(); --it) {
            std::cout << *it << " ";
            std::cout << std::endl;
        }
    }

    ~DoubleLinkedList() {
        while(head_) {
            DeleteHead();
        }
    }

// private:
node *head_;
node *tail_;
int size_;

};

#endif
