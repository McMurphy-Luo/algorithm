//
// Created by luojiayi on 5/18/17.
//

#ifndef ALGORITHM_DATA_STRUCTURE_RB_TREE_H
#define ALGORITHM_DATA_STRUCTURE_RB_TREE_H


#include "tree_node.h"


namespace algorithm
{
    template<typename KeyType, typename ValueType, int (*comparator)(const KeyType&, const KeyType&)>
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

        }

        ~RBTree()
        {
            
        }

        void put(const key_type& key, const value_type& value)
        {
            
        }

        value_type* remove(const key_type& key)
        {
            
        }

    private:
        node* root_;
    };
}

#endif //ALGORITHM_DATA_STRUCTURE_RB_TREE_H
