//
// Created by luojiayi on 5/18/17.
//

#ifndef ALGORITHM_DATA_STRUCTURE_RB_TREE_H
#define ALGORITHM_DATA_STRUCTURE_RB_TREE_H

#include <cassert>
#include "tree_node.h"

namespace algorithm
{
    template<typename KeyType, typename ValueType, int (*Comparator)(const KeyType&, const KeyType&)>
    class RBTree
    {
    public:
        typedef TreeNode<KeyType, ValueType> node;
        typedef typename node::key_type key_type;
        typedef typename node::value_type value_type;

    public:
        RBTree(): root_(nullptr)
        {
            
        }

        RBTree(const RBTree& another)
        {
            
        }

        RBTree& operator=(const RBTree& rhs){
            if (this == &rhs)
            {
                return *this;
            }
            clear();
            return *this;
        }

        ~RBTree()
        {
            clear();
        }

        void put(const key_type& key, const value_type& value)
        {
            // put node method, the algorithm is almost an implementation of pseudo code in <Introduction To Algorithm>
            if (!root_)
            {
                root_ = new node(key, value, nullptr, nullptr, nullptr, NodeColor::black);
                return;
            }
            node* maybe_target = fuzzy_find(key, root_->key);
            int compare_result = Comparator(key, maybe_target->key);
            if (compare_result == 0)
                // key is already exists in the tree, replacing value is enough
            {
                maybe_target->value = value;
                return;
            }
            node* new_node;
            if (compare_result > 0)
            {
                new_node = maybe_target->right = new node(key, value, maybe_target, nullptr, nullptr, NodeColor::red);
            }
            if (compare_result < 0)
            {
                new_node = maybe_target->left = new node(key, value, maybe_target, nullptr, nullptr, NodeColor::red);
            }
            if (new_node->parent->color == NodeColor::black) 
                // case 1 hit: parent of the new inserted node is black node
                // all red black tree property remains, so do nothing
            {
                return;
            }

            // from now, new_node->parent is red node
            



        }

        value_type* find(const key_type* key)
        {
            if (!root_)
            {
                return nullptr;
            }
            node* maybe_result = fuzzy_find(key, root_);
            int compare_result = Comparator(key, maybe_result->key);
            if (compare_result == 0)
            {
                return new value_type(maybe_result->value);
            }
            return nullptr;
        }

        value_type* remove(const key_type& key)
        {
            
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
        
        void inner_clear(node* which)
        {
            if (!which)
            {
                return;
            }
            inner_clear(which->left);
            inner_clear(which->right);
            delete which;
        }

        void inner_copy(node* which)
        {
            
        }

    private:
        node* root_;
    };
}

#endif //ALGORITHM_DATA_STRUCTURE_RB_TREE_H
