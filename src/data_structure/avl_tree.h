//
// Created by luojiayi on 5/20/17.
//

#ifndef ALGORITHM_DATA_STRUCTURE_AVL_TREE_H_
#define ALGORITHM_DATA_STRUCTURE_AVL_TREE_H_

#include <cassert>

namespace algorithm
{
namespace data_structure
{

template<typename KeyType, typename ValueType, typename Comparator>
class AVLTree {
public:
  typedef typename KeyType key_type;
  typedef typename ValueType value_type;

private:
  struct Node {
    key_type key;
    value_type value;
    Node* parent;
    Node* left;
    Node* right;
    size_t height;
  };

public:
  AVLTree()
    :root_(nullptr) {

  }

  AVLTree(const AVLTree& another) {

  }

  AVLTree& operator=(const AVLTree& rhs) {
    if (this == &rhs) {
        return *this;
    }
    Node* n = rhs.root_;

    root_ = new Node;
    

    return *this;
  }

  ~AVLTree() {
    if (!root_) {
      return;
    }
    RecurseDisposeNode(root_);
    root_ = nullptr;
  }

  void Put(const key_type& key, const value_type& value) {
    node* find_result = FuzzyFind(root_, key);
    if (!find_result) {
      root_ = new Node;
      root_->left = nullptr;
      root_->right = nullptr;
      root_->parent = nullptr;
      root_->key = key;
      root_->value = value;
      root_->height = 1;
    }
    int compare_result = Comparator(key, find_result->key);
    if (compare_result == 0) {
      find_result->value = value;
      return;
    }
    if (compare_result > 0) {
      find_result->right = new node(key, value, nullptr, nullptr, NodeColor::black);
    }
    if (compare_result < 0) {
      find_result->left = new node(key, value, nullptr, nullptr, NodeColor::black);
    }
    Blance(find_result);
  }

  value_type* Remove(const key_type& key) {

  }

private:
  void RecurseDisposeNode(Node* which) {
    if (which->left) {
      RecurseDisposeNode(which->left);
    }
    if (which->right) {
      RecurseDisposeNode(which->right);
    }
    delete which;
  }

  void Blance(Node* which) {
    size_type left_child_height = height(which->left);
    size_type right_child_height = height(which->right);
    int child_height_diff = left_child_height - right_child_height;
  }

  Node* FuzzyFind(Node* current, const key_type& key) {
    if (!current) {
      return nullptr;
    }
    int compare_result = Comparator(key, current->key);
    if (compare_result > 0) {
      if (!(current->right)) {
          return current;
      }
      return FuzzyFind(current->right, key);
    }
    if (compare_result < 0) {
      if (!(current->left)) {
          return current;
      }
      return FuzzyFind(current->left, key);
    }
    return current;
  }

private:
  Node* root_;
  Comparator comparator_;
  size_t size_;
};

}
}

#endif //ALGORITHM_DATA_STRUCTURE_AVL_TREE_H
