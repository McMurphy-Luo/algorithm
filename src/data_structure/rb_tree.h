/**
 * @author McMurphy.Luo
 * @date May/18/2017
 * @brief A self implementation of red black tree.
 * Red black tree is widely used in a lot of softwares and it is almost standard implementation of c++ std::map
 */

#ifndef ALGORITHM_DATA_STRUCTURE_RB_TREE_H_
#define ALGORITHM_DATA_STRUCTURE_RB_TREE_H_

#include <cassert>
#include <memory>

namespace algorithm
{
namespace data_structure
{

template<typename KeyType, typename ValueType, typename Comparator>
class RBTree
{
private:
  enum class NodeColor
  {
    Black,
    Red
  };

  struct Node
  {
    KeyType key;
    ValueType value;
    Node* left;
    Node* right;
    Node* parent;
    NodeColor color;
  };

public:
  RBTree(Comparator comparator)
    : root_(nullptr)
    , size_(0)
    , comparator_(comparator)
  {
    // do nothing
  }

  RBTree()
    : RBTree(Comparator())
  {
    // do nothing
  }

  RBTree(const RBTree& another)
    : RBTree(another.comparator_)
  {
    root_ = DeepClone(another.root_);
    size_ = another.size_;
  }

  RBTree& operator=(const RBTree& rhs)
  {
    if (this == &rhs) {
      return *this;
    }
    Clear();
    root_ = DeepClone(rhs.root_);
    size_ = rhs.size_;
    return *this;
  }

  ~RBTree()
  {
    Clear();
    root_ = nullptr;
  }

  bool Empty() const
  {
    return size_ == 0;
  }

  size_t Size() const
  {
    return size_;
  }

  void Put(const KeyType& key, const ValueType& value)
  {
    // put node method, the algorithm is almost an implementation of pseudo code from the book <Introduction To Algorithm>
    if (!root_) {
      assert(size_ == 0);
      root_ = new Node;
      root_->key = key;
      root_->value = value;
      root_->left = nullptr;
      root_->right = nullptr;
      root_->parent = nullptr;
      root_->color = NodeColor::Black;
      ++size_;
      return;
    }
    Node* maybe_target = FuzzyFind(key, root_);
    assert(maybe_target);
    bool should_before = comparator_(key, maybe_target->key);
    bool should_after = comparator_(maybe_target->key, key);
    assert(!(should_after && should_before));
    if (!should_before && !should_after) {
      // key is already exists in the tree, replacing value is enough
      maybe_target->value = value;
      return;
    }
    Node* new_node;
    if (should_after) {
      assert(!maybe_target->right);
      new_node = maybe_target->right = new Node;
      new_node->left = nullptr;
      new_node->right = nullptr;
      new_node->parent = maybe_target;
      new_node->key = key;
      new_node->value = value;
      new_node->color = NodeColor::Red;
    } else {
      assert(should_before);
      assert(!maybe_target->left);
      new_node = maybe_target->left = new Node;
      new_node->left = nullptr;
      new_node->right = nullptr;
      new_node->parent = maybe_target;
      new_node->key = key;
      new_node->value = value;
      new_node->color = NodeColor::Red;
    }
    ++size_;
    InsertFix(new_node);
  }

  /**
   * its user's resposibility to delete the returned
   */
  std::shared_ptr<ValueType> Find(const KeyType& key)
  {
    if (!root_) {
      return nullptr;
    }
    Node* maybe_result = FuzzyFind(key, root_);
    bool should_before = comparator_(key, maybe_result->key);
    bool should_after = comparator_(maybe_result->key, key);
    if (!should_before && !should_after) {
      return std::make_shared<ValueType>(maybe_result->value);
    }
    assert(!(should_before && should_after));
    return nullptr;
  }

  std::shared_ptr<ValueType> Remove(const KeyType& key)
  {
    if (!root_) {
      return nullptr;
    }
    Node* maybe_result = FuzzyFind(key, root_);
    bool should_before = comparator_(key, maybe_result->key);
    bool should_after = comparator_(maybe_result->key, key);
    assert(!(should_before && should_after));
    if (should_before && !should_after) {
      return nullptr;
    }
    if (!should_before && should_after) {
      return nullptr;
    }
    assert(!should_before && !should_after);
    // The target node that is required to be removed is found.
    std::shared_ptr<ValueType> result;
    if (!maybe_result->left && !maybe_result->right) {
      Node* parent = nullptr;
      if (!maybe_result->parent) {
        assert(maybe_result == root_);
        root_ = nullptr;
      }
      else if(maybe_result->parent->left == maybe_result) {
        maybe_result->parent->left = nullptr;
        parent = maybe_result->parent;
      }
      else if (maybe_result->parent->right == maybe_result) {
        maybe_result->parent->right = nullptr;
        parent = maybe_result->parent;
      }
      result = std::make_shared<ValueType>(maybe_result->value);
      if (parent) {
        RemoveFix(parent);
      }
      --size_;
      return result;
    }
    else if (maybe_result->left && !maybe_result->right) {

    }
    else if (!maybe_result->left && maybe_result->right) {
      
    }
    else {
      assert(maybe_result->left && maybe_result->right);

    }

    Node* successor = detach(maybe_result);
    if (maybe_result == root_) {
      root_ = successor;
    }
    value_type* result_value = new value_type(maybe_result->value);
    delete maybe_result;
    return result_value;
  }

  void Clear()
  {
    RecursiveDispose(root_);
    root_ = nullptr;
    size_ = 0;
  }

private:
  Node* FuzzyFind(const KeyType& key, Node* from)
  {
    bool should_before = comparator_(key, from->key);
    bool should_after = comparator_(from->key, key);
    if (!should_before && !should_after) {
      // The target node is found
      return from;
    }
    if (should_before) {
      if (!from->left) {
        // No further searching can be performed
        return from;
      }
      return FuzzyFind(key, from->left);
    }
    if (should_after) {
      // The target node has not been found and no further searching can be performed
      if (!from->right) {
        return from;
      }
      return FuzzyFind(key, from->right);
    }
    // If we reach here it means should_before == true and should_after == true
    // Which is not supposed to happen
    assert(false);
  }

  void RecursiveDispose(Node* which)
  {
    if (!which) {
      return;
    }
    RecursiveDispose(which->left);
    RecursiveDispose(which->right);
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
    result->color = which->color;
    result->left = DeepClone(which->left);
    result->right = DeepClone(which->right);
    return result;
  }

  void InsertFix(Node* which)
    // "which" may be the new inserted node or node on the path from the new node to root
    // In double red case
  {
    assert(which->color == NodeColor::red);
    if (which == root_ && which->color == NodeColor::red) {
      which->color = NodeColor::black;
      return;
    }

    if (which->parent->color == NodeColor::black) {
      // case 1 hit: parent of the new inserted node is black node
      // all red black tree property remains, so do nothing, insert fix finished.
      return;
    }
    // from now, new_node->parent is red node and node->parent->parent is always exists because root node
    // is black according to red black tree property, so new_node->parent must not be root node,
    // so that new_node->parent->parent must be exists.
    node* parent = which->parent;
    node* grand_parent = parent->parent;
    node* uncle;
    if (grand_parent->left == parent) {
      uncle = grand_parent->right;
    }
    // I don't want to use the 'else' keyword, even if it's faster
    if (grand_parent->right == parent) {
      uncle = grand_parent->left;
    }
    if (uncle && uncle->color == NodeColor::red) {
      // case 2 hit: parent of the new node is red node
      // uncle of the new node is red node
      uncle->color = NodeColor::black;
      parent->color = NodeColor::black;
      grand_parent->color = NodeColor::red;
      return insert_fix(grand_parent);
    }

    // from now, parent node is red node, and uncle node is black node
    // or uncle node is null
    if (parent == grand_parent->left) {
      if (which == parent->right) {
        left_rotate(parent);
      }
      right_rotate(grand_parent);
      // from now parent and child are changed, these two pointer loses their meanings
      // One thing is sure that the grand_parent replace the position of uncle previously
      grand_parent->color = NodeColor::red;
      grand_parent->parent->color = NodeColor::black;
      grand_parent->parent->left->color = NodeColor::red;
    }

    if (parent == grand_parent->right) {
      if (which == parent->left) {
        right_rotate(parent);
      }
      left_rotate(grand_parent);
      grand_parent->color = NodeColor::red;
      grand_parent->parent->color = NodeColor::black;
      grand_parent->parent->right->color = NodeColor::red;
    }
    if (root_ == grand_parent) {
      root_ = grand_parent->parent;
    }
  }

  void RemoveFix(Node* which)
  {

  }

private:
  Node* root_;
  size_t size_;
  Comparator comparator_;
};

}
}

#endif //ALGORITHM_DATA_STRUCTURE_RB_TREE_H_
