/**
 * @author McMurphy Luo
 * @date May/20/2017.
 * @brief A self implementation of avl tree which supports O(logN) finding and O(logN) random access
 * The avl tree is a highly blanced binary tree. Although it is not well-known as red black tree.
 * I think it is also a good choice for blanced binary tree.
 */

#ifndef ALGORITHM_DATA_STRUCTURE_AVL_TREE_H_
#define ALGORITHM_DATA_STRUCTURE_AVL_TREE_H_

#include <cassert>

namespace algorithm
{
namespace data_structure
{

template<typename KeyType, typename ValueType, typename Comparator>
class AVLTree
{
public:
  typedef typename KeyType key_type;
  typedef typename ValueType value_type;

private:
  struct Node
  {
    key_type key;
    value_type value;
    Node* parent;
    Node* left;
    Node* right;
    size_t height;
  };

public:
  AVLTree(Comparator comparator)
    : root_(nullptr)
    , comparator_(comparator)
    , size_(0)
  {

  }

  AVLTree()
    : AVLTree(Comparator())
  {

  }

  AVLTree(const AVLTree& another)
    : AVLTree(another.comparator_)
  {
    size_ = another.size_;
    root_ = DeepClone(another.root_);
  }

  AVLTree& operator=(const AVLTree& rhs)
  {
    if (this == &rhs) {
      return *this;
    }
    RecursiveDisposeNode(root_);
    root_ = DeepClone(rhs.root_);
    size_t = rhs.size_;
    return *this;
  }

  ~AVLTree()
  {
    RecursiveDisposeNode(root_);
  }

  size_t Size() const
  {
    return size_;
  }

  void Put(const key_type& key, const value_type& value)
  {
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

  value_type* Remove(const key_type& key)
  {

  }

private:
  void RecursiveDisposeNode(Node* which)
  {
    if (!which) {
      return;
    }
    if (which->left) {
      RecursiveDisposeNode(which->left);
    }
    if (which->right) {
      RecursiveDisposeNode(which->right);
    }
    delete which;
  }

  Node* DeepClone(Node* which)
  {
    if (!which) {
      return nullptr;
    }
    Node* result = new Node;
    result->key = which->key;
    result->value = which->value;
    result->parent = nullptr;
    result->left = DeepClone(which->left);
    if (result->left) {
      result->left->parent = result;
    }
    result->right = DeepClone(which->right);
    if (result->right) {
      result->right->parent = result;
    }
    result->height = which->height;
    return result;
  }

  void Blance(Node* which)
  {
    size_type left_child_height = height(which->left);
    size_type right_child_height = height(which->right);
    int child_height_diff = left_child_height - right_child_height;
  }

  Node* FuzzyFind(Node* current, const key_type& key)
  {
    if (!current) {
      return nullptr;
    }
    int compare_result = comparator_(key, current->key);
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
