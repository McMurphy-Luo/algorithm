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
            
        }

        void put(const key_type& key, const value_type& value)
        {
            if (!root_)
            {
                root_ = new node(key, value, nullptr, nullptr, nullptr, NodeColor::black);
                return;
            }
            node* current = root_;
            while(current)
            {
                int compare_result = Comparator(key, current->key);
                if (compare_result == 0)
                {
                    current->value = value;
                    return;
                }
                if (compare_result > 0)
                {
                    if (current->right)
                    {
                        current = current->right;
                        continue;
                    }
                    current->right = new node(key, value, current, nullptr, nullptr, NodeColor::red);
                    insert_fix();
                    return;
                }
                if (compare_result < 0)
                {
                    if (current->left)
                    {
                        current = current->left;
                        continue;
                    }
                    current->left = new node(key, value, current, nullptr, nullptr, NodeColor::red);
                    insert_fix();
                    return;
                }
                assert(false); // should never be here!
            }

        }

        value_type* remove(const key_type& key)
        {
            
        }

        void clear()
        {
            
        }

    protected:
        node* fuzzy_find(const key_type& key, node* from)
        {
            node* current = from;


        }

        void insert_fix()
        {
            
        }

        void remove_fix()
        {
            
        }

    private:
        node* root_;
    };
}

#endif //ALGORITHM_DATA_STRUCTURE_RB_TREE_H
