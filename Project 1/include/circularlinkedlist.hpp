#pragma once

#include <cstddef>
#include <iostream>

template <typename T>
class CircularList
{
private:
    struct ListNode {
        T value;
        ListNode* next;

        /* 
        Initialize value and next before entering the body and reject automatic conversion
        */
        explicit ListNode(const T& initial_value) : value(initial_value), next(nullptr) {}
    };

    ListNode* head = nullptr;

public:
    CircularList() = default;

    // destructor, calls delete on each node in the list
    ~CircularList() {
        if (head == nullptr) {
            return;
        }

        ListNode* current = head->next;
        while (current != head) {
            ListNode* next_node = current->next;
            delete current;
            current = next_node;
        }
        delete head;
    }
    /*
    Block list copying so we don't accidentaly copy a pointer
    "= delete" tells compiler to reject code trying to do =

    ...<Hat> a;
             b = a; rejected by first declaration
    ...<Hat> c;
             c = a; rejected by second declaration
    */
    CircularList(const CircularList&) = delete;
    CircularList& operator=(const CircularList&) = delete;


    // insert address of typedef T hat
    void insert(const T& hat) {
        // create new node
        ListNode* new_node = new ListNode(hat);

        // of the list is empty, insert the new node at the head
        if (head == nullptr) {
            head = new_node;
            new_node->next = head;
            return;
        }

        // traverse the list and find the end of the list
        ListNode* tail = head;
        while (tail->next != head) {
            tail = tail->next;
        }

        // insert the new node at the end of the list then attach it to the head.
        tail->next = new_node;
        new_node->next = head;
    }

    bool remove(const T& hat) {
        if (head == nullptr) {
            return false;
        }

        // Start previous at the tail so removing the head works correctly.
        ListNode* previous = head;
        while (previous->next != head) {
            previous = previous->next;
        }

        ListNode* current = head;
        // single entry list edge-case
        do {
            if (current->value == hat) {
                // The only node in the list points to itself.
                if (current->next == current) {
                    head = nullptr;
                } else {
                    previous->next = current->next;

                    if (current == head) {
                        head = current->next;
                    }
                }

                delete current;
                return true;
            }
            // traverse the list until you find the hat to remove
            previous = current;
            current = current->next;
        } while (current != head); // keep going until wrap back around to head
        // if we didn't find the hat, return false'
        return false;
    }

    void display() const {
        // empty list edge-case
        if (head == nullptr) {
            cout << "The hat collection is empty." << endl;
            return;
        }

        const ListNode* current = head;
        do {
            cout << current->value << endl;
            current = current->next;
        } while (current != head);
    }

    // Counts each hat by incrementing a pointer while traversing through the list
    // We save the head so we know when to stop by comparing to it
    size_t count() const {
        if (head == nullptr) {
            return 0;
        }

        size_t item_count = 0;
        const ListNode* current = head;
        do {
            ++item_count;
            current = current->next;
        } while (current != head);

        return item_count;
    }

    T& get(int index) {
        ListNode* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->value;
    }

    template <typename Action>
    void for_each(Action action) const {
        if (head == nullptr) {
            return;
        }

        const ListNode* current = head;
        do {
            action(current->value);
            current = current->next;
        } while (current != head);
    }
    

    template <typename Predicate>
    size_t search(Predicate is_match) const {
        if (head == nullptr) {
            return 0;
        }

        size_t match_count = 0;
        const ListNode* current = head;
        do {
            if (is_match(current->value)) {
                cout << current->value << endl;
                ++match_count;
            }
            current = current->next;
        } while (current != head);

        return match_count;
    }
};
