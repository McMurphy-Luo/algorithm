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
        template <typename KeyType, typename ValueType>
        struct BinarySubTree{
            typedef typename std::size_t size_type;

            BinarySubTree(const KeyType& key,
                          const ValueType& value,
                          BinarySubTree<KeyType, ValueType>* left,
                          BinarySubTree<KeyType, ValueType>* right):
                          key_(key),
                          value_(value),
                          left_(left),
                          right_(right)
            {
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

            KeyType key_;
            ValueType value_;
            BinarySubTree<KeyType, ValueType>* left_;
            BinarySubTree<KeyType, ValueType>* right_;
        };

        template <typename KeyType, typename ValueType>
        void get_least_node(BinarySubTree<KeyType, ValueType> *from, BinarySubTree<KeyType, ValueType>* from_parent, BinarySubTree<KeyType, ValueType> **target, BinarySubTree<KeyType, ValueType> **target_parent){
            assert(from);
            assert(!from_parent || (from_parent->left_ == from || from_parent->right_ == from));
            *target = from;
            *target_parent = from_parent;
            while((*target)->left_){
                *target_parent = *target;
                *target = (*target)->left_;
            }
        };

        template <typename KeyType, typename ValueType>
        void get_largest_node(BinarySubTree<KeyType, ValueType>* from, BinarySubTree<KeyType, ValueType>* from_parent, BinarySubTree<KeyType, ValueType> **target, BinarySubTree<KeyType, ValueType> **target_parent){
            assert(from);
            assert(!from_parent || (from_parent->left_ == from || from_parent->right_ == from));
            *target = from;
            *target_parent = from_parent;
            while((*target)->right_){
                *target_parent = *target;
                *target = (*target)->right_;
            }
        };

        template <typename KeyType, typename ValueType>
        void remove_leaf(BinarySubTree<KeyType, ValueType>* target, BinarySubTree<KeyType, ValueType>* parent){
            assert(target && parent);
            assert(target->left_ == nullptr && target->right_ == nullptr);
            assert(target == parent->left_ || target == parent->right_);
            if (target == parent->left_){
                parent->left_ = nullptr;
            }
            if (target == parent->right_){
                parent->right_ = nullptr;
            }
            assert(false); //  should never be here
        };

        template <typename KeyType, typename ValueType>
        void remove_one_child_node(BinarySubTree<KeyType, ValueType>* target, BinarySubTree<KeyType, ValueType>* parent){
            assert(target && parent);
            assert(target->left_ == nullptr && target->right_ || target->left_ && target->right_ == nullptr);
            assert(target == parent->left_ || target == parent->right_);
            BinarySubTree<KeyType, ValueType>* my_child = target->left_ ? target->left_ : target->right_;
            if (target == parent->left_){
                parent->left_ = my_child;
            }
            if (target == parent->right_){
                parent->right_ = my_child;
            }
            assert(false); //should never be here
        };

        template <typename KeyType, typename ValueType>
        void remove_two_children_node(BinarySubTree<KeyType, ValueType>* target, BinarySubTree<KeyType, ValueType>* parent){
            assert(target && parent);
            assert(target->left_ && target->right_);
            assert(target == parent->left_ || target == parent->right_);
            typename BinarySubTree<KeyType, ValueType>::size_type left_child_height = target->left_->height();
            typename BinarySubTree<KeyType, ValueType>::size_type right_child_height = target->right_->height();

            if (left_child_height >= right_child_height){
                BinarySubTree<KeyType, ValueType>* sub_tree_to_be_lifted;
                BinarySubTree<KeyType, ValueType>* parent_of_sub_tree_to_be_lifted;
                get_largest_node(target->left_, target, &sub_tree_to_be_lifted, &parent_of_sub_tree_to_be_lifted);

                assert(!sub_tree_to_be_lifted->right_);
                if (sub_tree_to_be_lifted->height() == 1){
                    remove_leaf(sub_tree_to_be_lifted, parent_of_sub_tree_to_be_lifted);
                } else {
                    remove_one_child_node(sub_tree_to_be_lifted, parent_of_sub_tree_to_be_lifted);
                }

                sub_tree_to_be_lifted->left_ = target->left_;
                sub_tree_to_be_lifted->right_ = target->right_;

                target->left_ = nullptr;
                target->left_ = nullptr;
                if (parent->left_ == target){
                    parent->left_ = sub_tree_to_be_lifted;
                }
                if (parent->right_ == target){
                    parent->right_ = sub_tree_to_be_lifted;
                }
            }
            if (right_child_height > left_child_height){
                BinarySubTree<KeyType, ValueType>* sub_tree_to_be_lifted;
                BinarySubTree<KeyType, ValueType>* parent_of_sub_tree_to_be_lifted;
                get_least_node(target->right_, target, &sub_tree_to_be_lifted, &parent_of_sub_tree_to_be_lifted);

                assert(!sub_tree_to_be_lifted->left_);
                switch(sub_tree_to_be_lifted->height()){
                    case 1:
                        remove_leaf(sub_tree_to_be_lifted, parent_of_sub_tree_to_be_lifted);
                        break;
                    default:
                        remove_one_child_node(sub_tree_to_be_lifted, parent_of_sub_tree_to_be_lifted);
                        break;
                }

                sub_tree_to_be_lifted->left_ = target->left_;
                sub_tree_to_be_lifted->right_ = target->right_;

                target->left_ = nullptr;
                target->left_ = nullptr;
                if (parent->left_ == target){
                    parent->left_ = sub_tree_to_be_lifted;
                }
                if (parent->right_ == target){
                    parent->right_ = sub_tree_to_be_lifted;
                }
            }
        };
    }



    template <typename KeyType, typename ValueType, int (*Comparator)(const KeyType&, const KeyType&)>
    class BinaryTree{
    public:
        typedef KeyType key_type;
        typedef ValueType value_type;
        typedef typename detail::BinarySubTree<KeyType, ValueType>::size_type size_type;
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
            if (!(result->left_) && !(result->right_)){
                detail::remove_leaf(result, result_parent);
            } else if (result->left_ && result->right_){
                detail::remove_two_children_node(result, result_parent);
            } else {
                detail::remove_one_child_node(result, result_parent);
            }
            value_type* result_value = new value_type(result->value_);
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
            return new value_type(result->value_);
        };

        void put(const key_type& key, const value_type& value){ // pre-order traversal
            detail::BinarySubTree<KeyType, ValueType>* result;
            detail::BinarySubTree<KeyType, ValueType>* result_parent;
            find_ex(key, &result, &result_parent);
            if (result){
                result->value_ = value;
                return;
            }
            if (!result_parent){
                root_ = new detail::BinarySubTree<key_type, value_type>(key, value, nullptr, nullptr);
                return;
            }
            int compare_result = Comparator(key, result_parent->key_);
            if (compare_result > 0){
                result_parent->right_ = new detail::BinarySubTree<key_type, value_type>(key, value, nullptr, nullptr);
                return;
            }
            if (compare_result < 0){
                result_parent->left_ = new detail::BinarySubTree<key_type, value_type>(key, value, nullptr, nullptr);
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
                compare_result = Comparator(key, (*target)->key_);
                if (compare_result != 0){
                    *target_parent = *target;
                }
                if (compare_result > 0){
                    *target = (*target)->right_;
                }
                if (compare_result < 0){
                    *target = (*target)->left_;
                }
            }
        };
        detail::BinarySubTree<KeyType, ValueType>* root_;
    };
}

#endif //ALGORITHM_DATA_STRUCTURE_BINARY_TREE_H
