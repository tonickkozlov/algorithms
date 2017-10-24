/** A simple linked list class. Should support following operations:
    - PushBack
    - PopBack
    - PushFront
    - PopFront

    - Insert
    - Reverse
 **/

#include <iostream>

struct ListNode {
    ListNode(int v): value(v), next(nullptr) {}
    int value;
    ListNode *next;
};

class MyList {
    public:
        MyList(): head_(nullptr), tail_(nullptr), size_(0) {}
        void PushBack(int value) {
            if (!head_) {
                head_ = new ListNode(value);
                tail_ = head_;
            } else {
                tail_->next = new ListNode(value);
                tail_ = tail_->next;
            }
            size_++;
        }
        void PushFront(int value) {
            if (!head_) {
                head_ = new ListNode(value);
                tail_ = head_;
            } else {
                ListNode *newHead = new ListNode(value);
                newHead->next = head_;
                head_ = newHead;
            }
            size_++;
        }
        int PopBack() {
            // find an element before tail_
            if (!head_) {
                return -1;
            }
            ListNode *beforeTail = head_;
            while (beforeTail->next != tail_) {
                beforeTail = beforeTail->next;
            }
            int value = tail_->value;
            delete tail_;
            size_ -= 1;
            tail_ = beforeTail;
            return value;
        }
        int PopFront() {
            if (!head_) {
                return -1;
            }
            int value = head_->value;
            ListNode *afterHead = head_->next;
            delete head_;
            head_ = afterHead;
            size_ -= 1;
            return value;
        }
        void Insert(int position, int value) {
            if (!head_) {
                return PushFront(value);
            } else if (position == (size_ - 1)) {
                return PushBack(value);
            } else if (position < 0 || position > (size_ - 1)) {
                return;
            }
            ListNode *tmp = head_;
            for (int i = 0; i < position; ++i) {
                tmp = tmp->next;
            }
            ListNode *next = tmp->next; //&1
            ListNode *newNode = new ListNode(value);// (100)
            newNode->next = next;// (100) -> 1
            tmp->next = newNode; // 0 -> 100 -> 1
            size_++;
        }
        void Reverse() {
            if (size_ == 0 || size_ == 1) {
                return;
            }
            ListNode *prev = nullptr, *curr = head_;
            tail_ = head_;
            while (curr != nullptr) {
                ListNode *next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
            }
            head_ = prev;
        }
        void print() {
            for (ListNode* node = head_; node; node = node->next) {
                std::cout << node->value << " ";
            }
            std::cout << std::endl;
        }
        int size() { return size_; }
    private:
        ListNode* head_;
        ListNode* tail_;
        int size_;
};
