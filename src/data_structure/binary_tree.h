//
// Created by luojiayi on 5/18/17.
//

#ifndef ALGORITHM_DATA_STRUCTURE_BINARY_TREE_H
#define ALGORITHM_DATA_STRUCTURE_BINARY_TREE_H


#include <cassert>
#include "tree_node.h"


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
            inner_copy(another.root_, &root_);
        };

        BinaryTree& operator=(const BinaryTree& to){
            clear();
            inner_copy(to.root_, &root_);
            return *this;
        }

        ~BinaryTree(){
            clear();
        };

        void clear(){ // post order traversal, delete all nodes
            inner_clear(root_);
            root_ = nullptr;
        }

        value_type* remove(const key_type& key){
            node* result = root_;
            node* result_parent = nullptr;
            find_ex(key, &result, &result_parent);
            if (!result){
                return nullptr;
            }
            node* successor = nullptr;
            if (!(result->left) && !(result->right)){
                successor = detach_leaf(result, result_parent);
            } else if (result->left && result->right){
                successor = detach_two_children_node(result, result_parent);
            } else {
                successor = detach_one_child_node(result, result_parent); // successor must exists because target at least contains one child
            }
            if (!result_parent){ // the node deleted has no parent node, so it must be root
                root_ = successor;
            }
            value_type* result_value = new value_type(result->value);
            delete result;
            return result_value;
        };

        size_type size() const {
            if (!root_){
                return 0;
            }
            return algorithm::size(root_);
        }

        value_type* find(const key_type& key){
            node* result = root_;
            node* result_parent = nullptr;
            find_ex(key, &result, &result_parent);
            if (!result){
                return nullptr;
            }
            return new value_type(result->value);
        };

        void put(const key_type& key, const value_type& value){
            node* result = root_;
            node* result_parent = nullptr;
            find_ex(key, &result, &result_parent);
            if (result){
                result->value = value;
                return;
            }
            node* new_node = new node;
            new_node->key = key;
            new_node->value = value;
            new_node->left = new_node->right = nullptr;
            if (!result_parent){ // the tree is empty
                root_ = new_node;
                return;
            }
            int compare_result = Comparator(key, result_parent->key);
            assert(compare_result);
            if (compare_result > 0){
                result_parent->right = new_node;
                return;
            }
            if (compare_result < 0){
                result_parent->left = new_node;
                return;
            }
        };

        const node* getRootNode() const
        {
            return root_;
        }

    protected:
        void find_ex(const key_type& key,
                     node **target,
                     node **target_parent)
        {
            if (!(*target)){
                return;
            }
            int compare_result = Comparator(key, (*target)->key);
            if (compare_result == 0){
                return;
            }
            *target_parent = *target;
            if (compare_result > 0){
                *target = (*target)->right;
                find_ex(key, target, target_parent);
            }
            if (compare_result < 0){
                *target = (*target)->left;
                find_ex(key, target, target_parent);
            }
        };

        void inner_clear(node* current){
            if (!current){
                return;
            }
            inner_clear(current->left);
            inner_clear(current->right);
            delete current;
        }

        void inner_copy(node* from, node** to){
            if (!from){
                return;
            }
            *to = new node(*from);
            inner_copy(from->left, &((*to)->left));
            inner_copy(from->right, &((*(to))->right));
        }

    private:
        node* root_;
    };
}

#endif //ALGORITHM_DATA_STRUCTURE_BINARY_TREE_H
