//
// Created by luojiayi on 5/18/17.
//

#ifndef ALGORITHM_DATA_STRUCTURE_RB_TREE_H
#define ALGORITHM_DATA_STRUCTURE_RB_TREE_H

#include <cassert>
#include "./tree_node.h"

namespace algorithm
{
    namespace data_structure
    {
        template<typename KeyType, typename ValueType, int(*Comparator)(const KeyType&, const KeyType&)>
        class RBTree
        {
        public:
            typedef TreeNode<KeyType, ValueType> node;
            typedef typename node::key_type key_type;
            typedef typename node::value_type value_type;

        public:
            RBTree():
                root_(nullptr)
            {
                // do nothing
            }

            RBTree(const RBTree& another)
            {
                inner_copy(another->root_);
            }

            RBTree& operator=(const RBTree& rhs)
            {
                if (this == &rhs) {
                    return *this;
                }
                clear();
                inner_copy(rhs.root_);
                return *this;
            }

            ~RBTree()
            {
                clear();
            }

            void put(const key_type& key, const value_type& value)
            {
                // put node method, the algorithm is almost an implementation of pseudo code in <Introduction To Algorithm>
                if (!root_) {
                    root_ = new node(key, value, nullptr, nullptr, nullptr, NodeColor::black);
                    return;
                }
                node* maybe_target = fuzzy_find(key, root_);
                int compare_result = Comparator(key, maybe_target->key);
                if (compare_result == 0) {
                    // key is already exists in the tree, replacing value is enough
                    maybe_target->value = value;
                    return;
                }
                node* new_node;
                if (compare_result > 0) {
                    new_node = maybe_target->right = new node(key, value, maybe_target, nullptr, nullptr, NodeColor::red);
                }
                if (compare_result < 0) {
                    new_node = maybe_target->left = new node(key, value, maybe_target, nullptr, nullptr, NodeColor::red);
                }
                insert_fix(new_node);
            }

            value_type* find(const key_type* key)
            {
                if (!root_) {
                    return nullptr;
                }
                node* maybe_result = fuzzy_find(key, root_);
                int compare_result = Comparator(key, maybe_result->key);
                if (compare_result == 0) {
                    return new value_type(maybe_result->value);
                }
                return nullptr;
            }

            value_type* remove(const key_type& key)
            {
                if (!root_) {
                    return nullptr;
                }
                node* maybe_result = fuzzy_find(key, root_);
                int compare_result = Comparator(key, maybe_result->key);
                if (compare_result != 0) {
                    // the key does not map to any value, so procedure end. return null.
                    return nullptr;
                }
                // from now on, maybe_result is the node of the key, and it is not null.
                node* successor = detach(maybe_result);
                if (maybe_result == root_) {
                    root_ = successor;
                }
                value_type* result_value = new value_type(maybe_result->value);
                delete maybe_result;
                return result_value;
            }

            void clear()
            {
                inner_clear(root_);
                root_ = nullptr;
            }

            const node* getRootNode() const
            {
                return root_;
            }

        protected:
            node* fuzzy_find(const key_type& key, node* from)
            {
                int compare_result = Comparator(key, from->key);
                if (compare_result > 0 && from->right) {
                    return fuzzy_find(key, from->right);
                }
                if (compare_result < 0 && from->left) {
                    return fuzzy_find(key, from->left);
                }
                return from;
            }

            void inner_clear(node* which)
            {
                if (!which) {
                    return;
                }
                inner_clear(which->left);
                inner_clear(which->right);
                delete which;
            }

            void inner_copy(node* which)
            {
                if (!which) {
                    return;
                }
                put(which->key, which->value);
                inner_copy(which->left);
                inner_copy(which->right);
            }

            void insert_fix(node* which)
                // "which" may be the new inserted node or node on the path from the new node to root
                // In double red case
            {
                assert(which->color == NodeColor::red);
                if (which == root_ && which->color == NodeColor::red) {
                    which->color = NodeColor::black;
                    return;
                }

                if (which->parent->color == NodeColor::black) {
                    // case 1 hit: parent of the new inserted node is black node
                    // all red black tree property remains, so do nothing, insert fix finished.
                    return;
                }
                // from now, new_node->parent is red node and node->parent->parent is always exists because root node
                // is black according to red black tree property, so new_node->parent must not be root node,
                // so that new_node->parent->parent must be exists.
                node* parent = which->parent;
                node* grand_parent = parent->parent;
                node* uncle;
                if (grand_parent->left == parent) {
                    uncle = grand_parent->right;
                }
                // I don't want to use the 'else' keyword, even if it's faster
                if (grand_parent->right == parent) {
                    uncle = grand_parent->left;
                }
                if (uncle && uncle->color == NodeColor::red) {
                    // case 2 hit: parent of the new node is red node
                    // uncle of the new node is red node
                    uncle->color = NodeColor::black;
                    parent->color = NodeColor::black;
                    grand_parent->color = NodeColor::red;
                    return insert_fix(grand_parent);
                }

                // from now, parent node is red node, and uncle node is black node
                // or uncle node is null
                if (parent == grand_parent->left) {
                    if (which == parent->right) {
                        left_rotate(parent);
                    }
                    right_rotate(grand_parent);
                    // from now parent and child are changed, these two pointer loses their meanings
                    // One thing is sure that the grand_parent replace the position of uncle previously
                    grand_parent->color = NodeColor::red;
                    grand_parent->parent->color = NodeColor::black;
                    grand_parent->parent->left->color = NodeColor::red;
                }

                if (parent == grand_parent->right) {
                    if (which == parent->left) {
                        right_rotate(parent);
                    }
                    left_rotate(grand_parent);
                    grand_parent->color = NodeColor::red;
                    grand_parent->parent->color = NodeColor::black;
                    grand_parent->parent->right->color = NodeColor::red;
                }
                if (root_ == grand_parent) {
                    root_ = grand_parent->parent;
                }
            }

            void remove_fix(node* which)
            {

            }

        private:
            node* root_;
        };
    }
}

#endif //ALGORITHM_DATA_STRUCTURE_RB_TREE_H
