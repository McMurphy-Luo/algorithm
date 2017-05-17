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

        void push(T data) {
            Node<T> *new_one = new Node<T>();
            new_one->payload = data;
            new_one->next = nullptr;
            new_one->previous = last_;
            last_ = new_one;
            ++length_;
            if (!first_) {
                first_ = new_one;
            }
        }

        T pop() {
            Node<T>* save_last_temporary = last_;
            last_ = last_->previous;
            if (last_) last_->next = nullptr;
            --length_;
            if (length_ == 0) first_ = nullptr;
            return save_last_temporary->payload;
        }

        T shift(){

        }

        void unshift(T data){

        }

    private:
        size_t length_;
        Node<T> *first_;
        Node<T> *last_;
    };
};

#endif //ALGORITHM_DATA_STRUCTURE_LINKED_LIST_H
