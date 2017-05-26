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
        template <typename KeyType, typename ValueType, int (*Comparator)(const KeyType&, const KeyType&)>
        class BinarySubTree{
        public:
            friend class BinaryTree<KeyType, ValueType, Comparator>;
            typedef std::size_t size_type;
            typedef KeyType key_type;
            typedef ValueType value_type;

        protected:
            static void remove_leaf(BinarySubTree* target, BinarySubTree* parent){
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

            static void remove_one_child_node(BinarySubTree* target, BinarySubTree* parent){
                assert(target && parent);
                assert(target->left_ == nullptr && target->right_ || target->left_ && target->right_ == nullptr);
                assert(target == parent->left_ || target == parent->right_);
                BinarySubTree* my_child = target->left_ ? target->left_ : target->right_;
                if (target == parent->left_){
                    parent->left_ = my_child;
                }
                if (target == parent->right_){
                    parent->right_ = my_child;
                }
                assert(false); //should never be here
            };

            static void remove_two_children_node(BinarySubTree* target, BinarySubTree* parent){
                assert(target && parent);
                assert(target->left_ && target->right_);
                assert(target == parent->left_ || target == parent->right_);
                size_type left_child_height = target->left_->height();
                size_type right_child_height = target->right_->height();

                if (left_child_height >= right_child_height){
                    BinarySubTree* sub_tree_to_be_lifted;
                    BinarySubTree* parent_of_sub_tree_to_be_lifted;
                    target->left_->get_largest_node(&sub_tree_to_be_lifted, &parent_of_sub_tree_to_be_lifted);


                }
                if (right_child_height > left_child_height){

                }



            };

        public:
            BinarySubTree(const key_type& key,
                          const value_type& value,
                          BinarySubTree* left,
                          BinarySubTree* right):
                          key_(key),
                          value_(value),
                          left_(left),
                          right_(right)
            {
            };

            BinarySubTree(const BinarySubTree& another){

            };

            BinarySubTree& operator=(const BinarySubTree& rhs){
                return *this;
            };

            virtual ~BinarySubTree(){
                clear();
            };

            BinarySubTree* find(const key_type& key){
                int compare_result = Comparator(key, key_);
                if (compare_result == 0){
                    return this;
                }
                if (compare_result > 0){
                    if (right_ == nullptr){
                        return nullptr;
                    }
                    return right_->find(key);
                }
                if (compare_result < 0){
                    if (left_ == nullptr){
                        return nullptr;
                    }
                    return left_->find(key);
                }
                assert(false); // could never be here
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

            void clear(){ //post order traversal
                if (left_) {
                    left_->clear();
                    delete left_;
                    left_ = nullptr;
                }
                if (right_){
                    right_->clear();
                    delete right_;
                    right_ = nullptr;
                }
            };

        protected:
            void get_least_node(BinarySubTree **target, BinarySubTree **target_parent){
                *target_parent = this;
                *target = this->left_;
                while(*target){
                    *target_parent = *target;
                    *target = (*target)->left_;
                }
            };

            void get_largest_node(BinarySubTree **target, BinarySubTree **target_parent){
                *target_parent = this;
                *target = this->right_;
                while(*target){
                    *target_parent = *target;
                    *target = (*target)->left_;
                }
            };

            key_type key_;
            value_type value_;
            BinarySubTree* left_;
            BinarySubTree* right_;
        };
    }



    template <typename KeyType, typename ValueType, int (*Comparator)(const KeyType&, const KeyType&)>
    class BinaryTree{
    public:
        typedef detail::BinarySubTree::key_type  key_type;
        typedef detail::BinarySubTree::value_type value_type;
        typedef detail::BinarySubTree::size_type size_type;
    public:
        BinaryTree():
                root_(nullptr)
        {
        };

        value_type remove(const key_type& key){

        };

        void put(const key_type& key, const value_type& value){ // pre-order traversal
            if (!root_){
                root_ = new detail::BinarySubTree(key, value, nullptr, nullptr);
            }

        };

    protected:
        void find_ex(const key_type& key,
                     detail::BinarySubTree **target,
                     detail::BinarySubTree **target_parent)
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
        detail::BinarySubTree* root_;
    };
}

#endif //ALGORITHM_DATA_STRUCTURE_BINARY_TREE_H
