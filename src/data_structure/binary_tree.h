//
// Created by luojiayi on 5/18/17.
//

#ifndef ALGORITHM_DATA_STRUCTURE_BINARY_TREE_H
#define ALGORITHM_DATA_STRUCTURE_BINARY_TREE_H

#include <cstddef>
#include <cassert>
#include "../config.h"

namespace algorithm{
    namespace detail{
        template <typename KeyType, typename ValueType, int (*Comparator)(const KeyType&, const KeyType&)>
        class BinarySubTree{
        public:
            typedef std::size_t size_type;
            typedef KeyType key_type;
            typedef ValueType value_type;
        protected:
            enum class Direction{
                left,
                right,
                none
            };

        public:
            BinarySubTree(const key_type& key,
                          const value_type& value,
                          BinarySubTree* parent,
                          Direction direction,
                          BinarySubTree* left,
                          BinarySubTree* right):
                          key_(key),
                          value_(value),
                          parent_(parent),
                          left_(left),
                          right_(right)
            {
                assert(
                        direction == Direction::left && parent->left_ == this ||
                        direction == Direction::none && !parent ||
                        direction == Direction::right && parent->right_ == this
                );
            };

            BinarySubTree(const BinarySubTree& another){

            };

            BinarySubTree& operator=(const BinarySubTree& rhs){
                return *this;
            };

            ~BinarySubTree(){
                clear();
            };

            value_type *find(const key_type& key){
                BinarySubTree* search_result = accurate_search(key);
                if (search_result == nullptr){
                    return nullptr;
                }
                return new value_type(search_result->value_);
            };

            void put(const key_type& key, const value_type& value){ // pre-order traversal
                int compare_result = Comparator(key, key_);
                if (compare_result == 0){
                    this->value_ = value;
                    return;
                }
                if (compare_result < 0){
                    if (left_){
                        left_->put(key, value);
                        return;
                    }
                    left_ = new BinarySubTree(key, value, this, Direction::left, nullptr, nullptr);
                    return;
                }
                if (compare_result > 0){
                    if (right_){
                        right_->put(key, value);
                        return;
                    }
                    right_ = new BinarySubTree(key, value, this, Direction::right, nullptr, nullptr);
                    return;
                }
            };

            value_type *remove(const key_type& key){ // a sub tree will remove itself and alter its (sub tree and parent)'s pointer
                int compare_result = Comparator(key, key_);
                if (compare_result < 0){ // the node to be removed is in the left sub tree
                    if (left_){
                        return left_->remove(key);
                    }
                    return nullptr;
                }
                if (compare_result > 0){  // the sub tree to be removed is in the right sub tree
                    if (right_){
                        return right_->remove(key);
                    }
                    return nullptr;
                }
                // now I am sure i am going to be removed
                if (!left_ && !right_){ // I am leaf
                    value_type* result = new value_type(value_);
                    if (parent_){
                        switch(direction_){
                            case Direction::left:
                                parent_->left_ = nullptr;
                                break;
                            case Direction::right:
                                parent_->right_ = nullptr;
                                break;
                            default:
                                assert(false); // should never be here
                                break;
                        }
                    }
                    delete this;
                    return result;
                }

                size_t left_sub_tree_height = left_ ? left_->height() : 0;
                size_t right_sub_tree_height = right_ ? right_->height() : 0;

                BinarySubTree* sub_tree_to_be_alter = left_sub_tree_height > right_sub_tree_height ? left_ : right_;


            };

            size_type size() const {    // post order traversal
                size_type left_sub_tree_size = left_ ? left_->size() : 0;
                size_type right_sub_tree_size = right_ ? right_->size() : 0;
                return left_sub_tree_size + right_sub_tree_size + 1;
            };

            size_type height() const {  // post order traversal
                size_type left_sub_tree_height = left_ ? left_->height(): 0;
                size_type right_sub_tree_height = right_ ? right_->height() : 0;
                return 1 + (
                        right_sub_tree_height > left_sub_tree_height ? right_sub_tree_height : left_sub_tree_height
                );
            };

            void clear(){ //post order traversal
                if (left_) {
                    left_->clear();
                    delete left_;
                    left_ = nullptr;
                }
                if (right_){
                    right_->clear();
                    delete right_;
                    right_ = nullptr;
                }
            };

        protected:
            BinarySubTree* accurate_search(const key_type& key){
                int compare_result = Comparator(key, key_);
                if (compare_result == 0){
                    return this;
                }
                if (compare_result > 0){
                    if (right_ == nullptr){
                        return nullptr;
                    }
                    return right_->accurate_search(key);
                }
                if (compare_result < 0){
                    if (left_ == nullptr){
                        return nullptr;
                    }
                    return left_->accurate_search(key);
                }
                assert(false); // could never be here
            };

            void promote_sub_tree_to_self(BinarySubTree* sub_tree){
                if (parent_){
                    switch(direction_){
                        case Direction::left:
                            parent_->left_ = sub_tree;
                            break;
                        case Direction::right:
                            parent_->right_ = sub_tree;
                            break;
                        default:
                            assert(false); //should never be here
                    }
                }

            }

            key_type key_;
            value_type value_;
            BinarySubTree* parent_;
            Direction direction_;
            BinarySubTree* left_;
            BinarySubTree* right_;
        };
    }



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
            if (!root_) {                     // So it's user's duty to delete the object.
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
