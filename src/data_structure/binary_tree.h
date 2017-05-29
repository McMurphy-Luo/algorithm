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
        typedef typename std::size_t size_type;
        template <typename KeyType, typename ValueType>
        struct TreeNode{
            typedef KeyType key_type;
            typedef ValueType value_type;
            key_type key;
            value_type value;
            TreeNode<key_type, value_type>* left;
            TreeNode<key_type, value_type>* right;
        };

        template<typename KeyType, typename ValueType>
        size_type size(const TreeNode<KeyType, ValueType>* which) {    // post order traversal
            assert(which);
            size_type left_sub_tree_size = which->left ? size(which->left) : 0;
            size_type right_sub_tree_size = which->right ? size(which->right) : 0;
            return left_sub_tree_size + right_sub_tree_size + 1;
        };

        template<typename KeyType, typename ValueType>
        size_type height(const TreeNode<KeyType, ValueType>* which) {  // post order traversal
            assert(which);
            size_type left_sub_tree_height = which->left ? height(which->left): 0;
            size_type right_sub_tree_height = which->right ? height(which->right) : 0;
            return 1 + (
                    right_sub_tree_height > left_sub_tree_height ? right_sub_tree_height : left_sub_tree_height
            );
        };

        template <typename KeyType, typename ValueType>
        void get_least_node(TreeNode<KeyType, ValueType> *from, TreeNode<KeyType, ValueType>* from_parent, TreeNode<KeyType, ValueType> **target, TreeNode<KeyType, ValueType> **target_parent){
            assert(from);
            assert(!from_parent || (from_parent->left == from || from_parent->right == from));
            *target = from;
            *target_parent = from_parent;
            while((*target)->left){
                *target_parent = *target;
                *target = (*target)->left;
            }
        };

        template <typename KeyType, typename ValueType>
        void get_largest_node(TreeNode<KeyType, ValueType>* from, TreeNode<KeyType, ValueType>* from_parent, TreeNode<KeyType, ValueType> **target, TreeNode<KeyType, ValueType> **target_parent){
            assert(from);
            assert(!from_parent || (from_parent->left == from || from_parent->right == from));
            *target = from;
            *target_parent = from_parent;
            while((*target)->right){
                *target_parent = *target;
                *target = (*target)->right;
            }
        };

        // leaf does not have any successor, it always return nullptr.
        template <typename KeyType, typename ValueType>
        TreeNode<KeyType, ValueType>* detach_leaf(TreeNode<KeyType, ValueType>* target, TreeNode<KeyType, ValueType>* parent){
            assert(target);
            assert(target->left == nullptr && target->right == nullptr);
            assert(!parent || target == parent->left || target == parent->right);
            if (!parent){
                return nullptr;
            }
            if (target == parent->left){
                parent->left = nullptr;
            }
            if (target == parent->right){
                parent->right = nullptr;
            }
            return nullptr;
        };

        //detach the target node from the tree, replace the target with the successor of it and return the successor.
        template <typename KeyType, typename ValueType>
        TreeNode<KeyType, ValueType>* detach_one_child_node(TreeNode<KeyType, ValueType>* target, TreeNode<KeyType, ValueType>* parent){
            assert(target);
            assert((target->left == nullptr && target->right) || (target->left && target->right == nullptr));
            assert(!parent || target == parent->left || target == parent->right);
            TreeNode<KeyType, ValueType>* my_child = target->left ? target->left : target->right;
            target->left = target->right = nullptr;
            if (!parent){ // no parent, target must be root
                return my_child;
            }
            if (target == parent->left){
                parent->left = my_child;
            }
            if (target == parent->right){
                parent->right = my_child;
            }
            return my_child;
        };

        //detach the target node from the tree and return the successor of target
        template <typename KeyType, typename ValueType>
        TreeNode<KeyType, ValueType>* detach_two_children_node(TreeNode<KeyType, ValueType>* target, TreeNode<KeyType, ValueType>* parent){
            assert(target);
            assert(target->left && target->right);
            assert(!parent || target == parent->left || target == parent->right);
            size_type left_child_height = height(target->left);
            size_type right_child_height = height(target->right);

            TreeNode<KeyType, ValueType>* sub_tree_to_be_lifted;
            TreeNode<KeyType, ValueType>* parent_of_sub_tree_to_be_lifted;
            if (left_child_height >= right_child_height){
                get_largest_node(target->left, target, &sub_tree_to_be_lifted, &parent_of_sub_tree_to_be_lifted);
                assert(!sub_tree_to_be_lifted->right);
            } else {
                get_least_node(target->right, target, &sub_tree_to_be_lifted, &parent_of_sub_tree_to_be_lifted);
                assert(!sub_tree_to_be_lifted->left);
            }

            if (height(sub_tree_to_be_lifted) == 1){
                detach_leaf(sub_tree_to_be_lifted, parent_of_sub_tree_to_be_lifted);
            } else {
                detach_one_child_node(sub_tree_to_be_lifted, parent_of_sub_tree_to_be_lifted);
            }
            sub_tree_to_be_lifted->left = target->left;
            sub_tree_to_be_lifted->right = target->right;
            target->left = nullptr;
            target->right = nullptr;
            if (parent && parent->left == target){
                parent->left = sub_tree_to_be_lifted;
            }
            if (parent && parent->right == target){
                parent->right = sub_tree_to_be_lifted;
            }
            return sub_tree_to_be_lifted;
        };
    }

    template <typename KeyType, typename ValueType,  int (*Comparator)(const KeyType&, const KeyType&)>
    class BinaryTree{
    public:
        typedef typename detail::TreeNode<KeyType, ValueType>::key_type key_type;
        typedef typename detail::TreeNode<KeyType, ValueType>::value_type value_type;
        typedef detail::size_type size_type;
    protected:
        typedef detail::TreeNode<KeyType, ValueType> node;
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
                successor = detail::detach_leaf(result, result_parent);
            } else if (result->left && result->right){
                successor = detail::detach_two_children_node(result, result_parent);
            } else {
                successor = detail::detach_one_child_node(result, result_parent); // successor must exists because target at least contains one child
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
            return detail::size(root_);
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

        node* root_;
    };
}

#endif //ALGORITHM_DATA_STRUCTURE_BINARY_TREE_H
