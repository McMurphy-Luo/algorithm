//
// Created by luojiayi on 5/18/17.
//

#ifndef ALGORITHM_DATA_STRUCTURE_BINARY_TREE_H
#define ALGORITHM_DATA_STRUCTURE_BINARY_TREE_H

#include <cstddef>
#include <cassert>
#include <functional>
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

        template <typename KeyType, typename ValueType>
        void detach_leaf(TreeNode<KeyType, ValueType>* target, TreeNode<KeyType, ValueType>* parent){
            assert(target);
            assert(target->left == nullptr && target->right == nullptr);
            assert(!parent || target == parent->left || target == parent->right);
            if (!parent){
                return;
            }
            if (target == parent->left){
                parent->left = nullptr;
            }
            if (target == parent->right){
                parent->right = nullptr;
            }
            assert(false); //  should never be here
        };

        template <typename KeyType, typename ValueType>
        void detach_one_child_node(TreeNode<KeyType, ValueType>* target, TreeNode<KeyType, ValueType>* parent){
            assert(target);
            assert(target->left == nullptr && target->right || target->left && target->right == nullptr);
            assert(!parent || target == parent->left || target == parent->right);
            TreeNode<KeyType, ValueType>* my_child = target->left ? target->left : target->right;
            if (!parent){
                return;
            }
            if (target == parent->left){
                parent->left = my_child;
            }
            if (target == parent->right){
                parent->right = my_child;
            }
            assert(false); //should never be here
        };

        template <typename KeyType, typename ValueType>
        void detach_two_children_node(TreeNode<KeyType, ValueType>* target, TreeNode<KeyType, ValueType>* parent){
            assert(target);
            assert(target->left && target->right);
            assert(!parent || target == parent->left || target == parent->right);
            size_type left_child_height = height(target->left);
            size_type right_child_height = height(target->right);

            if (left_child_height >= right_child_height){
                TreeNode<KeyType, ValueType>* sub_tree_to_be_lifted;
                TreeNode<KeyType, ValueType>* parent_of_sub_tree_to_be_lifted;
                get_largest_node(target->left, target, &sub_tree_to_be_lifted, &parent_of_sub_tree_to_be_lifted);

                assert(!sub_tree_to_be_lifted->right);
                if (height(sub_tree_to_be_lifted) == 1){
                    detach_leaf(sub_tree_to_be_lifted, parent_of_sub_tree_to_be_lifted);
                } else {
                    detach_one_child_node(sub_tree_to_be_lifted, parent_of_sub_tree_to_be_lifted);
                }

                sub_tree_to_be_lifted->left = target->left;
                sub_tree_to_be_lifted->right = target->right;

                target->left = nullptr;
                target->left = nullptr;
                if (parent->left == target){
                    parent->left = sub_tree_to_be_lifted;
                }
                if (parent->right == target){
                    parent->right = sub_tree_to_be_lifted;
                }
            }
            if (right_child_height > left_child_height){
                TreeNode<KeyType, ValueType>* sub_tree_to_be_lifted;
                TreeNode<KeyType, ValueType>* parent_of_sub_tree_to_be_lifted;
                get_least_node(target->right, target, &sub_tree_to_be_lifted, &parent_of_sub_tree_to_be_lifted);

                assert(!sub_tree_to_be_lifted->left);
                switch(height(sub_tree_to_be_lifted)){
                    case 1:
                        detach_leaf(sub_tree_to_be_lifted, parent_of_sub_tree_to_be_lifted);
                        break;
                    default:
                        detach_one_child_node(sub_tree_to_be_lifted, parent_of_sub_tree_to_be_lifted);
                        break;
                }

                sub_tree_to_be_lifted->left = target->left;
                sub_tree_to_be_lifted->right = target->right;

                target->left = nullptr;
                target->left = nullptr;
                if (parent->left == target){
                    parent->left = sub_tree_to_be_lifted;
                }
                if (parent->right == target){
                    parent->right = sub_tree_to_be_lifted;
                }
            }
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

        value_type* remove(const key_type& key){
            node* result;
            node* result_parent;
            find_ex(key, &result, &result_parent);
            if (!result){
                return nullptr;
            }
            if (!(result->left) && !(result->right)){
                detail::detach_leaf(result, result_parent);
            } else if (result->left && result->right){
                detail::detach_two_children_node(result, result_parent);
            } else {
                detail::detach_one_child_node(result, result_parent);
            }
            value_type* result_value = new value_type(result->value);
            delete result;
            if (!result_parent){
                root_ = nullptr;
            }
            return result_value;
        };

        value_type* find(const key_type& key){
            node* result;
            node* result_parent;
            find_ex(key, &result, &result_parent);
            if (!result){
                return nullptr;
            }
            return new value_type(result->value);
        };

        void put(const key_type& key, const value_type& value){ // pre-order traversal
            node* result;
            node* result_parent;
            find_ex(key, &result, &result_parent);
            if (result){
                result->value = value;
                return;
            }
            node* new_node = new node;
            new_node->key = key;
            new_node->value = value;
            new_node->left = new_node->right = nullptr;
            if (!result_parent){
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
            assert(false);
        };

    protected:
        void find_ex(const key_type& key,
                     node **target,
                     node **target_parent)
        {
            *target = root_;
            *target_parent = nullptr;
            int compare_result = 1;

            while(*target){
                compare_result = Comparator(key, (*target)->key);
                if (compare_result == 0){
                    break;
                }
                *target_parent = *target;
                if (compare_result > 0){
                    *target = (*target)->right;
                }
                if (compare_result < 0){
                    *target = (*target)->left;
                }
            }
        };
        node* root_;
    };
}

#endif //ALGORITHM_DATA_STRUCTURE_BINARY_TREE_H
