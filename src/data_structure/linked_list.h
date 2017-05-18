//
// Created by luojiayi on 5/16/17.
//

#ifndef ALGORITHM_DATA_STRUCTURE_LINKED_LIST_H
#define ALGORITHM_DATA_STRUCTURE_LINKED_LIST_H

#include <cstddef>

namespace algorithm {
    template<typename T>
    struct Node {
        T payload;
        Node<T> *previous;
        Node<T> *next;
    };

    template<typename T>
    class LinkedList {
    public:
        LinkedList(): length_(0),
                first_(nullptr),
                last_(nullptr)
        {
        }

        size_t length() const {
            return length_;
        };

        T get(size_t index) const{
            return this[index];
        };

        T& operator[](size_t index){
            Node<T> *temporary_item = first_;
            while(index){
                temporary_item = temporary_item->next;
                index--;
            }
            return temporary_item->payload;
        };

        void push(T data) {
            Node<T> *new_one = new Node<T>();
            new_one->payload = data;
            new_one->next = nullptr;
            new_one->previous = last_;
            last_ = new_one;
            if (!first_) {
                first_ = new_one;
            }
            ++length_;
        }

        T pop() {
            Node<T> *save_last_temporary = last_;
            last_ = last_->previous; // if there is no item in the list just seg fault
            if (last_) last_->next = nullptr; // when the list contains more than 2 items
            --length_;
            if (length_ == 0) first_ = nullptr;
            return save_last_temporary->payload;
        }

        T shift(){
            Node<T> *save_first_temporary = first_;
            first_ = first_->next; // if there is no item in the list, just seg fault
            if (first_) first_->previous = nullptr;
            --length_;
            if (length_ == 0) last_ = nullptr;
            return save_first_temporary->payload;
        }

        void unshift(T data){
            Node<T> *new_node = new Node<T>();
            new_node->payload = data;
            new_node->next = first_;
            new_node->previous = nullptr;
            if (first_) first_->previous = new_node;
            first_ = new_node;
            if(!last_){
                last_ = new_node;
            }
            ++length_;
        }

    private:
        size_t length_;
        Node<T> *first_;
        Node<T> *last_;
    };
};

#endif //ALGORITHM_DATA_STRUCTURE_LINKED_LIST_H
