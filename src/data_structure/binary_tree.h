//
// Created by luojiayi on 5/18/17.
//

#ifndef ALGORITHM_DATA_STRUCTURE_BINARY_TREE_H
#define ALGORITHM_DATA_STRUCTURE_BINARY_TREE_H

#include <cassert>
#include "./tree_node.h"

namespace algorithm{
    template <typename KeyType, typename ValueType,  int (*Comparator)(const KeyType&, const KeyType&)>
    class BinaryTree{
    public:
        typedef typename TreeNode<KeyType, ValueType>::key_type key_type;
        typedef typename TreeNode<KeyType, ValueType>::value_type value_type;
        typedef TreeNode<KeyType, ValueType> node;

    public:
        BinaryTree():
                root_(nullptr)
        {
        };

        BinaryTree(const BinaryTree& another):
                BinaryTree(){
            inner_copy(another.root_);
        };

        BinaryTree& operator=(const BinaryTree& to){
            clear();
            inner_copy(to.root_);
            return *this;
        }

        ~BinaryTree(){
            clear();
        };

        void clear(){ // post order traversal, delete all nodes
            inner_clear(root_);
            root_ = nullptr;
        }

        // It's the user's duty to delete the returned value
        value_type* remove(const key_type& key){
            if (!root_)
            {
                return nullptr;
            }

            node* maybe_result = fuzzy_find(key, root_);
            int compare_result = Comparator(key, maybe_result->key);
            if (compare_result != 0)
            {
                return nullptr;
            }

            node* successor = detach(maybe_result);
            if (maybe_result == root_)
            {
                root_ = successor;
            }
            value_type* result_value = new value_type(maybe_result->value);
            delete maybe_result;
            return result_value;
        }

        size_type size() const {
            return algorithm::size(root_);
        }

        value_type* find(const key_type& key){
            if (!root_)
            {
                return nullptr;
            }
            node* maybe_target = fuzzy_find(key, root_);
            int compare_result = Comparator(key, maybe_target->key);
            if (compare_result == 0)
            {
                return new value_type(maybe_target->value);
            }
            return nullptr;
        }

        void put(const key_type& key, const value_type& value){
            if (!root_){
                root_ = new node(key, value, nullptr, nullptr, nullptr, NodeColor::black);
                return;
            }

            node* maybe_target = fuzzy_find(key, root_);
            int compare_result = Comparator(key, maybe_target->key);
            if (compare_result == 0)
            {
                maybe_target->value = value;
            }
            if (compare_result > 0)
            {
                maybe_target->right = new node(key, value, maybe_target, nullptr, nullptr, NodeColor::black);
            }
            if (compare_result < 0)
            {
                maybe_target->left = new node(key, value, maybe_target, nullptr, nullptr, NodeColor::black);
            }
        }

        const node* getRootNode() const
        {
            return root_;
        }

    protected:
        node* fuzzy_find(key_type key, node* from)
        {
            int compare_result = Comparator(key, from->key);
            if (compare_result > 0 && from->right)
            {
                return fuzzy_find(key, from->right);
            }
            if (compare_result < 0 && from->left)
            {
                return fuzzy_find(key, from->left);
            }
            return from;
        }

        void inner_clear(node* current){
            if (!current){
                return;
            }
            inner_clear(current->left);
            inner_clear(current->right);
            delete current;
        }

        void inner_copy(node* from){
            if (!from)
            {
                return;
            }
            put(from->key, from->value);
            inner_copy(from->left);
            inner_copy(from->right);
        }

    private:
        node* root_;
    };
}

#endif //ALGORITHM_DATA_STRUCTURE_BINARY_TREE_H
