//
// Created by luojiayi on 5/20/17.
//

#ifndef ALGORITHM_DATA_STRUCTURE_AVL_TREE_H
#define ALGORITHM_DATA_STRUCTURE_AVL_TREE_H

#include <cassert>
#include "./tree_node.h"

namespace algorithm
{
  namespace data_structure
  {
    template<typename KeyType, typename ValueType, typedef Comparator>
    class AVLTree {
    public:
      typedef typename KeyType key_type;
      typedef typename ValueType value_type;

    private:
      struct Node {
        key_type key;
        value_type value;
        node *parent;
        node *left;
        node *right;
        size_t height;
      };

    public:
      AVLTree() :root_(nullptr) {

      }

      AVLTree(const AVLTree& another) {

      }

      AVLTree& operator=(const AVLTree& rhs) {
        if (this == &rhs) {
            return *this;
        }
        return *this;
      }

      ~AVLTree() {

      }

      void put(const key_type& key, const value_type& value)
      {
        node* find_result = fuzzy_find(root_, key);
        if (!find_result) {
          root_ = new node(key, value, nullptr, nullptr, NodeColor::black);
        }
        int compare_result = Comparator(key, find_result->key);
        if (compare_result == 0) {
          find_result->value = value;
        }
        if (compare_result > 0) {
          find_result->right = new node(key, value, nullptr, nullptr, NodeColor::black);
        }
        if (compare_result < 0) {
          find_result->left = new node(key, value, nullptr, nullptr, NodeColor::black);
        }
        assert(false);
      }

      value_type* remove(const key_type& key)
      {

      }


    protected:
      void blance_node(node* which)
      {
        size_type left_child_height = height(which->left);
        size_type right_child_height = height(which->right);
        int child_height_diff = left_child_height - right_child_height;
      }

      node* fuzzy_find(node* current, const key_type& key)
      {
        if (!current) {
          return nullptr;
        }
        int compare_result = Comparator(key, current->key);
        if (compare_result > 0) {
          if (!(current->right)) {
              return current;
          }
          return find(current->right, key);
        }
        if (compare_result < 0) {
          if (!(current->left)) {
              return current;
          }
          return find(current->left, key);
        }
        return current;
      }

    private:
      node* root_;
      Comparator comparator_;
    };
  }
}

#endif //ALGORITHM_DATA_STRUCTURE_AVL_TREE_H
