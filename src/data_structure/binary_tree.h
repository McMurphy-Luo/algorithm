//
// Created by luojiayi on 5/18/17.
//

#ifndef ALGORITHM_DATA_STRUCTURE_BINARY_TREE_H
#define ALGORITHM_DATA_STRUCTURE_BINARY_TREE_H

#include <cstddef>

namespace algorithm{
    template <typename KeyType, typename ValueType, int (*Comparator)(const KeyType&, const KeyType&)>
    class BinaryTree{
    public:
        typedef std::size_t size_type;
        typedef KeyType key_type;
        typedef ValueType value_type;

    protected:
        struct Node{
            key_type key;
            value_type value;
            Node* left;
            Node* right;
        };

    public:
        BinaryTree(): root_(nullptr) {

        };

        BinaryTree(const BinaryTree &another){

        };

        BinaryTree& operator=(const BinaryTree& rhs){
            return *this;
        };

        const value_type& operator[](const key_type& rhs) const {

        };

        ~BinaryTree(){
            clear();
        };

        value_type* get(const key_type& key){ // create object on heap, I don't want to use boost::optional or std::pair etc.
            if (!root_) {                     // It's user's duty to delete the object.
                return nullptr;
            }
            Node* result = fuzzy_search(root_, key);
            int compare_result = Comparator(key, result->key);
            if (compare_result == 0){
                return nullptr;
            }
            return new value_type(result->value);
        };

        void put(const key_type& key, const value_type& value){
            if (!root_){
                root_ = new Node;
                root_->key = key;
                root_->value = value;
                root_->left = nullptr;
                root_->right = nullptr;
            }
            Node* search_result = fuzzy_search(root_, key);
            int compare_result = Comparator(key, search_result->value);
            if (compare_result == 0){  // if node already exists, replace it with new value
                search_result->value = value;  // the value type should implement operator= plus copy ctor
            }
            Node* new_node = new Node;
            new_node->key = key;
            new_node->value = value;
            new_node->left = nullptr;
            new_node->right = nullptr;
            if (compare_result > 0){
                search_result->right = new_node;
            }
            if (compare_result < 0){
                search_result->left = new_node;
            }
        };

        void remove(const key_type& key){

        };

        bool isEmpty() const {
            return root_ == nullptr;
        };

        size_type size() const {

        };

        void clear(){ // simply post order traverse the tree delete every node

        };

    protected:
        Node* fuzzy_search(Node* from, const key_type& key){ // from must be a valid pointer, otherwise segfaults
            int compare_result = Comparator(key, from->key);
            if (compare_result > 0 && from->right){
                return fuzzy_search(from->right, key);
            }
            if (compare_result < 0 && from->left){
                return fuzzy_search(from->left, key);
            }
            return from;
        };
        
        Node* root_;
    };
}

#endif //ALGORITHM_DATA_STRUCTURE_BINARY_TREE_H
