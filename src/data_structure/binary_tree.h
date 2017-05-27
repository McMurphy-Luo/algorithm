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
        struct BinarySubTree{
            BinarySubTree(const KeyType& key,
                          const ValueType& value,
                          BinarySubTree<KeyType, ValueType>* left,
                          BinarySubTree<KeyType, ValueType>* right):
                          key(key),
                          value(value),
                          left(left),
                          right(right)
            {
            };

            size_type size() const {    // post order traversal
                size_type left_sub_tree_size = left ? left->size() : 0;
                size_type right_sub_tree_size = right ? right->size() : 0;
                return left_sub_tree_size + right_sub_tree_size + 1;
            };

            size_type height() const {  // post order traversal
                size_type left_sub_tree_height = left ? left->height(): 0;
                size_type right_sub_tree_height = right ? right->height() : 0;
                return 1 + (
                    right_sub_tree_height > left_sub_tree_height ? right_sub_tree_height : left_sub_tree_height
                );
            };

            KeyType key;
            ValueType value;
            BinarySubTree<KeyType, ValueType>* left;
            BinarySubTree<KeyType, ValueType>* right;
        };

        template <typename KeyType, typename ValueType>
        void get_least_node(BinarySubTree<KeyType, ValueType> *from, BinarySubTree<KeyType, ValueType>* from_parent, BinarySubTree<KeyType, ValueType> **target, BinarySubTree<KeyType, ValueType> **target_parent){
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
        void get_largest_node(BinarySubTree<KeyType, ValueType>* from, BinarySubTree<KeyType, ValueType>* from_parent, BinarySubTree<KeyType, ValueType> **target, BinarySubTree<KeyType, ValueType> **target_parent){
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
        void remove_leaf(BinarySubTree<KeyType, ValueType>* target, BinarySubTree<KeyType, ValueType>* parent){
            assert(target && parent);
            assert(target->left == nullptr && target->right == nullptr);
            assert(target == parent->left || target == parent->right);
            if (target == parent->left){
                parent->left = nullptr;
            }
            if (target == parent->right){
                parent->right = nullptr;
            }
            assert(false); //  should never be here
        };

        template <typename KeyType, typename ValueType>
        void remove_one_child_node(BinarySubTree<KeyType, ValueType>* target, BinarySubTree<KeyType, ValueType>* parent){
            assert(target && parent);
            assert(target->left == nullptr && target->right || target->left && target->right == nullptr);
            assert(target == parent->left || target == parent->right);
            BinarySubTree<KeyType, ValueType>* my_child = target->left ? target->left : target->right;
            if (target == parent->left){
                parent->left = my_child;
            }
            if (target == parent->right){
                parent->right = my_child;
            }
            assert(false); //should never be here
        };

        template <typename KeyType, typename ValueType>
        void remove_two_children_node(BinarySubTree<KeyType, ValueType>* target, BinarySubTree<KeyType, ValueType>* parent){
            assert(target && parent);
            assert(target->left && target->right);
            assert(target == parent->left || target == parent->right);
            size_type left_child_height = target->left->height();
            size_type right_child_height = target->right->height();

            if (left_child_height >= right_child_height){
                BinarySubTree<KeyType, ValueType>* sub_tree_to_be_lifted;
                BinarySubTree<KeyType, ValueType>* parent_of_sub_tree_to_be_lifted;
                get_largest_node(target->left, target, &sub_tree_to_be_lifted, &parent_of_sub_tree_to_be_lifted);

                assert(!sub_tree_to_be_lifted->right);
                if (sub_tree_to_be_lifted->height() == 1){
                    remove_leaf(sub_tree_to_be_lifted, parent_of_sub_tree_to_be_lifted);
                } else {
                    remove_one_child_node(sub_tree_to_be_lifted, parent_of_sub_tree_to_be_lifted);
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
                BinarySubTree<KeyType, ValueType>* sub_tree_to_be_lifted;
                BinarySubTree<KeyType, ValueType>* parent_of_sub_tree_to_be_lifted;
                get_least_node(target->right, target, &sub_tree_to_be_lifted, &parent_of_sub_tree_to_be_lifted);

                assert(!sub_tree_to_be_lifted->left);
                switch(sub_tree_to_be_lifted->height()){
                    case 1:
                        remove_leaf(sub_tree_to_be_lifted, parent_of_sub_tree_to_be_lifted);
                        break;
                    default:
                        remove_one_child_node(sub_tree_to_be_lifted, parent_of_sub_tree_to_be_lifted);
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

    template <typename KeyType, typename ValueType, int (*Comparator)(const KeyType&, const KeyType&)>
    class BinaryTree{
    public:
        typedef KeyType key_type;
        typedef ValueType value_type;
        typedef detail::size_type size_type;
    public:
        BinaryTree():
                root_(nullptr)
        {
        };

        value_type* remove(const key_type& key){
            detail::BinarySubTree<KeyType, ValueType>* result;
            detail::BinarySubTree<KeyType, ValueType>* result_parent;
            find_ex(key, &result, &result_parent);
            if (!result){
                return nullptr;
            }
            if (!(result->left) && !(result->right)){
                detail::remove_leaf(result, result_parent);
            } else if (result->left && result->right){
                detail::remove_two_children_node(result, result_parent);
            } else {
                detail::remove_one_child_node(result, result_parent);
            }
            value_type* result_value = new value_type(result->value);
            delete result;
            if (!result_parent){
                root_ = nullptr;
            }
            return result_value;
        };

        value_type* find(const key_type& key){
            detail::BinarySubTree<KeyType, ValueType>* result;
            detail::BinarySubTree<KeyType, ValueType>* result_parent;
            find_ex(key, &result, &result_parent);
            if (!result){
                return nullptr;
            }
            return new value_type(result->value);
        };

        void put(const key_type& key, const value_type& value){ // pre-order traversal
            detail::BinarySubTree<KeyType, ValueType>* result;
            detail::BinarySubTree<KeyType, ValueType>* result_parent;
            find_ex(key, &result, &result_parent);
            if (result){
                result->value = value;
                return;
            }
            if (!result_parent){
                root_ = new detail::BinarySubTree<key_type, value_type>(key, value, nullptr, nullptr);
                return;
            }
            int compare_result = Comparator(key, result_parent->key);
            if (compare_result > 0){
                result_parent->right = new detail::BinarySubTree<key_type, value_type>(key, value, nullptr, nullptr);
                return;
            }
            if (compare_result < 0){
                result_parent->left = new detail::BinarySubTree<key_type, value_type>(key, value, nullptr, nullptr);
                return;
            }
            assert(false);
        };

    protected:
        void find_ex(const key_type& key,
                     detail::BinarySubTree<KeyType, ValueType> **target,
                     detail::BinarySubTree<KeyType, ValueType> **target_parent)
        {
            *target = root_;
            *target_parent = nullptr;
            int compare_result = 1;

            while(compare_result != 0 && *target){
                compare_result = Comparator(key, (*target)->key);
                if (compare_result != 0){
                    *target_parent = *target;
                }
                if (compare_result > 0){
                    *target = (*target)->right;
                }
                if (compare_result < 0){
                    *target = (*target)->left;
                }
            }
        };
        detail::BinarySubTree<KeyType, ValueType>* root_;
    };
}

#endif //ALGORITHM_DATA_STRUCTURE_BINARY_TREE_H
