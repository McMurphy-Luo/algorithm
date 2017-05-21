//
// Created by luojiayi on 5/16/17.
//

#ifndef ALGORITHM_DATA_STRUCTURE_LINKED_LIST_H
#define ALGORITHM_DATA_STRUCTURE_LINKED_LIST_H
#include "../config.h"
#include <cstddef>
#include <cassert>
#ifdef DATA_STRUCTURE_DEBUG
#include <cstring>
#include <string>
#endif


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

        LinkedList(const LinkedList &another): LinkedList()
        {
            Node* current = another.first_;
            while(current){
                add(current->payload);
                current = current->next;
            }
        }

        LinkedList& operator=(const LinkedList &rhs){
            if (this == &rhs) return *this;
            length_ = rhs.length_;
            first_ = last_ = nullptr;
            Node* current = rhs.first_;
            while(current){
                add(current->payload);
                current = current->next;
            }
            return *this;
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
            return (*this)[index];
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
        };

        // The linked list should at least contains 1 node, otherwise segfault.
        value_type remove(size_type index){
            length_--;
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
            current->previous->next = current->next;
            current->next->previous = current->previous;
            value_type temp = current->payload;
            delete current;
            return temp;
        };

        void insert(const value_type &data, size_type before){
            Node* following_node = first_;
            while(before){
                following_node = following_node->next;
                --before;
            }
            if (following_node == nullptr) { // the list must be empty
                return add(data);
            }
            ++length_;
            Node* new_node = new Node;
            new_node->payload = data;
            if (following_node->previous == nullptr){ // the new node is inserted into the list head
                assert(following_node == first_); // following node equals first_
                following_node->previous = new_node;
                new_node->next = following_node;
                new_node->previous = nullptr;
                first_ = new_node;
                return;
            }
            following_node->previous->next = new_node;
            new_node->previous = following_node->previous;
            following_node->previous = new_node;
            new_node->next = following_node;
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
#ifdef DATA_STRUCTURE_DEBUG
    public:
        std::string toString(){
            std::string result;

            std::size_t len = 0;
            Node* current = first_;
            while(len < length_){
                char buf[BUFSIZ];
                memset(buf, 0, BUFSIZ);
                snprintf(buf, BUFSIZ, "Node index is %ju, Node content is ", len);
                result.append(buf);
                result.append(current->payload);
                result.append("\n");
                ++len;
                current = current->next;
            }
            return result;
        };
#endif



    protected:
        size_type length_;
        Node *first_;
        Node *last_;
    };
};

#endif //ALGORITHM_DATA_STRUCTURE_LINKED_LIST_H
