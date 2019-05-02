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
#include <utility>

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
    size_t height; // The height of subtree, 1 for leaf node
    size_t size; // The node count of subtree, 1 for leaf node
  };

public:
  AVLTree(Comparator comparator)
    : root_(nullptr)
    , comparator_(comparator)
  {

  }

  AVLTree()
    : AVLTree(Comparator())
  {

  }

  AVLTree(const AVLTree& another)
    : AVLTree(another.comparator_)
  {
    root_ = DeepClone(another.root_);
  }

  AVLTree& operator=(const AVLTree& rhs)
  {
    if (this == &rhs) {
      return *this;
    }
    comparator_ = rhs.comparator_;
    RecursiveDisposeNode(root_);
    root_ = DeepClone(rhs.root_);
    return *this;
  }

  ~AVLTree()
  {
    RecursiveDisposeNode(root_);
  }

  size_t Size() const
  {
    if (!root_) {
      return 0;
    }
    return root_->size;
  }

  std::pair<key_type, value_type> At(size_t index)
  {
    // No need to check if root_ is nullptr. Let it crash if user call this function when the tree is empty
    Node* target_node = FindByIndex(root_, index);
    return std::make_pair(target_node->key, target_node->value);
  }

  const std::pair<key_type, value_type> At(size_t index) const
  {
    // No need to check if root_ is nullptr. Let it crash if user call this function when the tree is empty
    Node* target_node = FindByIndex(root_, index);
    return std::make_pair(target_node->key, target_node->value);
  }

  std::shared_ptr<value_type> Find(const key_type& key) const
  {
    Node* find_result = FuzzyFind(root_, key);
    if (!find_result) {
      assert(!root_);
      return nullptr;
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
      root_->size = 1;
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
    new_node->size = 1;
    if (should_before) {
      find_result->left = new_node;
    } else {
      assert(should_after);
      find_result->right = new_node;
    }
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
    std::shared_ptr<value_type> result = std::make_shared<value_type>(target_node_to_remove->value);
    Node* parent = target_node_to_remove->parent;
    if (!target_node_to_remove->right && !target_node_to_remove->left) {
      if (!parent) {
        assert(target_node_to_remove == root_);
        root_ = nullptr;
      }
      else if (parent->left == target_node_to_remove) {
        parent->left = nullptr;
      }
      else if (parent->right == target_node_to_remove) {
        parent->right = nullptr;
      }
      else {
        assert(false);
      }
      delete target_node_to_remove;
      Blance(parent);
    }
    else if (!target_node_to_remove->right && target_node_to_remove->left) {
      if (!parent) {
        assert(target_node_to_remove == root_);
        root_ = target_node_to_remove->left;
        root_->parent = nullptr;
      }
      else if (parent->left == target_node_to_remove) {
        parent->left = target_node_to_remove->left;
        parent->left->parent = parent;
      }
      else if (parent->right == target_node_to_remove) {
        parent->right = target_node_to_remove;
        parent->right->parent = parent;
      }
      else {
        assert(false);
      }
      delete target_node_to_remove;
      Blance(parent);
    }
    else if (target_node_to_remove->right && !target_node_to_remove->left) {
      if (!parent) {
        assert(target_node_to_remove == root_);
        root_ = target_node_to_remove->right;
        root_->parent = nullptr;
      }
      else if (parent->left == target_node_to_remove) {
        parent->left = target_node_to_remove->right;
        parent->left->parent = parent;
      }
      else if (parent->right == target_node_to_remove) {
        parent->right = target_node_to_remove->right;
        parent->right->parent = parent;
      }
      else {
        assert(false);
      }
      delete target_node_to_remove;
      Blance(parent);
    }
    else {
      assert(target_node_to_remove->right && target_node_to_remove->left);
      Node* successor = nullptr;
      Node* parent_of_successor = target_node_to_remove;
      if (target_node_to_remove->left->height < target_node_to_remove->right->height) {
        successor = target_node_to_remove->left;
        while (successor->right) {
          successor = successor->right;
        }
        assert(!successor->right);
        successor->parent->right = successor->left;
        parent_of_successor = successor->parent;
        if (successor->left) {
          successor->left->parent = successor->parent;
        }
      }
      else {
        assert(target_node_to_remove->left->height >= target_node_to_remove->right->height);
        successor = target_node_to_remove->right;
        while (successor->left) {
          successor = successor->left;
        }
        assert(!successor->left);
        successor->parent->left = successor->right;
        parent_of_successor = successor->parent;
        if (successor->right) {
          successor->right->parent = successor->parent;
        }
      }
      if (root_ == target_node_to_remove) {
        root_ = successor;
      }
      successor->left = target_node_to_remove->left;
      successor->right = target_node_to_remove->right;
      successor->left->parent = successor;
      successor->right->parent = successor;
      successor->parent = target_node_to_remove->parent;
      if (parent_of_successor == target_node_to_remove) {
        Blance(successor);
      }
      else {
        Blance(parent_of_successor);
      }
      delete target_node_to_remove;
    }
    return result;
  }

  void Clear()
  {
    RecursiveDisposeNode(root_);
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
    result->size = which->size;
    return result;
  }

  void Remeasure(Node* target)
  {
    while (target) {
      target->height = std::max((target->left ? target->left->height : 0), (target->right ? target->right->height : 0)) + 1;
      target->size = (target->left ? target->left->size : 0) + (target->right ? target->right->size : 0) + 1;
      target = target->parent;
    }
  }

  void Blance(Node* which)
  {
    Remeasure(which);
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

  Node* FindByIndex(Node* current, size_t index) const
  {
    size_t left_tree_size = current->left ? current->left->size : 0;
    if (index < left_tree_size) {
      return FindByIndex(current->left, index);
    }
    size_t next_index = index - left_tree_size;
    if (next_index == 0) {
      return current;
    }
    return FindByIndex(current->right, next_index - 1);
  }

private:
  Node* root_;
  Comparator comparator_;
};

}
}

#endif //ALGORITHM_DATA_STRUCTURE_AVL_TREE_H
