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
#include <memory>

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
    size_ = rhs.size_;
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

  std::shared_ptr<value_type> Find(const key_type& key) const
  {
    Node* find_result = FuzzyFind(root_, key);
    if (!find_result) {
      assert(!root_);
    }
    bool should_before = comparator_(key, find_result->key);
    bool should_after = comparator_(find_result->key, key);
    assert(!(should_before && should_after));
    if (!should_before && !should_after) {
      return std::make_shared<value_type>(find_result->value);
    }
    return nullptr;
  }

  void Put(const key_type& key, const value_type& value)
  {
    Node* find_result = FuzzyFind(root_, key);
    if (!find_result) {
      root_ = new Node;
      root_->left = nullptr;
      root_->right = nullptr;
      root_->parent = nullptr;
      root_->key = key;
      root_->value = value;
      root_->height = 1;
      ++size_;
      return;
    }
    bool should_before = comparator_(key, find_result->key);
    bool should_after = comparator_(find_result->key, key);
    if (!should_before && !should_after) {
      find_result->value = value;
      return;
    }
    assert(!(should_after && should_before));
    Node* new_node = new Node;
    new_node->key = key;
    new_node->value = value;
    new_node->parent = find_result;
    new_node->height = 1;
    new_node->left = nullptr;
    new_node->right = nullptr;
    new_node->parent = find_result;
    if (should_before) {
      find_result->left = new_node;
    } else {
      assert(should_after);
      find_result->right = new_node;
    }
    Node* parent = new_node->parent;
    while (parent) {
      parent->height = std::max((parent->left ? parent->left->height : 0), (parent->right ? parent->right->height : 0)) + 1;
      parent = parent->parent;
    }
    ++size_;
    Blance(new_node);
  }

  std::shared_ptr<value_type> Remove(const key_type& key)
  {
    Node* target_node_to_remove = FuzzyFind(root_, key);
    if (!target_node_to_remove) {
      assert(!root_);
      return nullptr;
    }
    bool should_before = comparator_(key, target_node_to_remove->key);
    bool should_after = comparator_(target_node_to_remove->key, key);
    assert(!(should_before && should_after));
    if (should_before || should_after) {
      return nullptr;
    }
    assert(!should_before && !should_after);
    std::shared_ptr<value_type> result = target_node_to_remove->value;
    Node* parent = traget_node_to_remove->parent;
    if (!parent) {
      assert(target_node_to_remove == root_);
    }

    do {
      if (!target_node_to_remove->right && !target_node_to_remove->left) {
        if (!parent) {
          root_ = nullptr;
          delete target_node_to_remove;
          break;
        }
      }

    } while (0);
    return result;
  }

  void Clear()
  {
    RecursiveDisposeNode(root_);
    size_ = 0;
    root_ = nullptr;
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

  Node* DeepClone(Node* which) const
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
    
  }

  Node* FuzzyFind(Node* current, const key_type& key) const
  {
    if (!current) {
      return nullptr;
    }
    bool should_before = comparator_(key, current->key);
    bool should_after = comparator_(current->key, key);
    assert(!(should_before && should_after));
    if (!should_before && !should_after) {
      return current;
    }
    if (should_before) {
      if (!current->left) {
        return current;
      }
      return FuzzyFind(current->left, key);
    }
    assert(should_after);
    if (!current->right) {
      return current;
    }
    return FuzzyFind(current->right, key);
  }

private:
  Node* root_;
  Comparator comparator_;
  size_t size_;
};

}
}

#endif //ALGORITHM_DATA_STRUCTURE_AVL_TREE_H
