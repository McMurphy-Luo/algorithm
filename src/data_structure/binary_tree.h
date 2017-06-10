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
            node* current = root_;
            while(current){
                int compare_result = Comparator(key, current->key);
                if (compare_result > 0){
                    current = current->right;
                }
                if (compare_result < 0){
                    current = current->left;
                }
                if (compare_result == 0){
                    node* successor = detach(current);
                    if (current == root_){
                        root_ = successor;
                    }
                    value_type* result_value = new value_type(current->value);
                    delete current;
                    return result_value;
                }
            }
            return nullptr;
        }

        size_type size() const {
            if (!root_){
                return 0;
            }
            return algorithm::size(root_);
        }

        value_type* find(const key_type& key){
            node* current = root_;
            while(current){
                int compare_result = Comparator(key, current->key);
                if (compare_result > 0){
                    current = current->right;
                }
                if (compare_result < 0){
                    current = current->left;
                }
                if (compare_result == 0){
                    return new value_type(current->value);
                }
            }
            return nullptr;
        }

        void put(const key_type& key, const value_type& value){
            if (!root_){
                root_ = new node(key, value, nullptr, nullptr, nullptr, NodeColor::black);
            }
            node* current = root_;
            while(current){
                int compare_result = Comparator(key, current->key);
                if (compare_result == 0){
                    current->value = value;
                }
                if (compare_result > 0){
                    if (current->right){
                        current = current->right;
                        continue;
                    } else {
                        current->right = new node(key, value, current, nullptr, nullptr, NodeColor::black);
                        return;
                    }
                }
                if (compare_result < 0){
                    if (current->left){
                        current = current->left;
                        continue;
                    } else {
                        current->left = new node(key, value, current, nullptr, nullptr, NodeColor::black);
                        return;
                    }
                }
            }
        };

        const node* getRootNode() const
        {
            return root_;
        }

    protected:
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
