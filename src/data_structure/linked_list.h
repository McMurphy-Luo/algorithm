//
// Created by luojiayi on 5/16/17.
//

#ifndef ALGORITHM_DATA_STRUCTURE_LINKED_LIST_H
#define ALGORITHM_DATA_STRUCTURE_LINKED_LIST_H

#include <cstddef>

namespace algorithm {
    template<typename T>
    class LinkedList {
    public:
        typedef T value_type;
        typedef std::size_t size_type;

    protected:
        struct Node {
            T payload;
            Node *previous;
            Node *next;
        };

    public:
        LinkedList(): length_(0),
                first_(nullptr),
                last_(nullptr) {};

        LinkedList(const LinkedList &another){

        }

        ~LinkedList(){
            Node *current_ = first_;
            while(current_){
                delete current_;
                current_ = current_->next;
            }
        }

        size_type size() const {
            return length_;
        };

        value_type get(size_type index) {
            return this->operator[](index);
        };

        value_type& operator[](size_type index) {
            Node *temporary_item = first_;
            while(index){
                temporary_item = temporary_item->next;
                --index;
            }
            return temporary_item->payload;
        };

        void add(const value_type &data) {
            Node *new_one = new Node;
            new_one->payload = data;
            new_one->next = nullptr;
            new_one->previous = last_;
            ++length_;
            if (!first_) {
                first_ = last_ = new_one;
                return;
            }
            last_->next = new_one;
            last_ = new_one;
            return;
        };

        // The linked list should at least contains 1 node, otherwise segfault.
        value_type remove(size_type index){
            Node *current = first_;
            while(index){
                current = first_->next;
                index--;
            }
            if (current == first_) { // I am the first node
                first_ = last_ = nullptr;
                value_type temp = current->payload;
                delete current;
                return temp;
            }
            if (current == last_){ // I am the last node
                current->previous->next = nullptr;
                value_type temp = current->payload;
                delete current;
                return temp;
            }
            current->previous = current->next;
            current->next = current->previous;
            value_type temp = current->payload;
            delete current;
            return temp;
        };

        void insert(const value_type &data, size_type after){

        };

        void clear(){
            length_ = 0;
            Node* current = first_;
            Node* next = current->next;
            while(current){
                delete current;
                current = next;
            }
        };

    protected:
        size_type length_;
        Node *first_;
        Node *last_;
    };
};

#endif //ALGORITHM_DATA_STRUCTURE_LINKED_LIST_H
