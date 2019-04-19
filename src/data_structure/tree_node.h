#ifndef ALGORITHM_DATA_STRUCTURE_TREE_NODE_H
#define ALGORITHM_DATA_STRUCTURE_TREE_NODE_H

#include <cassert>

namespace algorithm
{
namespace data_structure
{

typedef int size_type;
/*
* The only one node type for avl tree, red black tree, trivial binary tree.
* In avl tree and trivial binary tree, node color is always black.
*/
template <typename KeyType, typename ValueType>
struct TreeNode
{
    typedef KeyType key_type;
    typedef ValueType value_type;
    typedef TreeNode<key_type, value_type> node;
    TreeNode(
        key_type key,
        value_type value,
        node *parent,
        node *left,
        node *right,
        node_color color
    ) : key(key), value(value), parent(parent), left(left), right(right), color(color) {}
    TreeNode(const TreeNode& another) :
        TreeNode(another.key, another.value, another.parent, another.left, another.right, another.color) {}
    key_type key;
    value_type value;
    node *parent;
    node *left;
    node *right;
    node_color color;
};

template<typename KeyType, typename ValueType>
size_type size(const TreeNode<KeyType, ValueType>* which) // post order traversal
{
    if (!which) { // empty node size is 0
        return 0;
    }
    return size(which->left) + size(which->right) + 1;
}

template<typename KeyType, typename ValueType>
size_type height(const TreeNode<KeyType, ValueType>* which) // post order traversal
{
    if (!which) { // empty node height is 0
        return 0;
    }
    size_type left_sub_tree_height = height(which->left);
    size_type right_sub_tree_height = height(which->right);
    return 1 + (
        right_sub_tree_height > left_sub_tree_height ? right_sub_tree_height : left_sub_tree_height
        );
}

template <typename KeyType, typename ValueType>
TreeNode<KeyType, ValueType>* get_least_node(TreeNode<KeyType, ValueType> *from)
{
    while (from->left) {
        from = from->left;
    }
    return from;
}

template <typename KeyType, typename ValueType>
TreeNode<KeyType, ValueType>* get_largest_node(TreeNode<KeyType, ValueType>* from)
{
    while (from->right) {
        from = from->right;
    }
    return from;
}

template<typename KeyType, typename ValueType>
void replace(TreeNode<KeyType, ValueType>* which, TreeNode<KeyType, ValueType>* to)
{
  if (which->parent) {
    if (which->parent->left == which) {
      which->parent->left = to;
    }
    if (which->parent->right == which) {
      which->parent->right = to;
    }
  }
  if (to) {
    to->parent = which->parent;
    to->left = which->left;
    to->right = which->right;
  }
}

template<typename KeyType, typename ValueType>
void detach_leaf(TreeNode<KeyType, ValueType>* which)
{
  assert(which);
  assert(!(which->left) && !(which->right));
  replace<KeyType, ValueType>(which, nullptr);
}

template<typename KeyType, typename ValueType>
TreeNode<KeyType, ValueType>* detach_one_child_node(TreeNode<KeyType, ValueType>* which)
{
  std::cout << "node1" << std::endl;
  assert((which->left && !(which->right)) || (!(which->left) && which->right));
  TreeNode<KeyType, ValueType>* successor = which->left ? which->left : which->right;
  replace(which, successor);
  return successor;
}

template<typename KeyType, typename ValueType>
TreeNode<KeyType, ValueType>* detach_two_child_node(TreeNode<KeyType, ValueType> *which)
{
  size_type left_height = height(which->left);
  size_type right_height = height(which->right);
  TreeNode<KeyType, ValueType>* replacement;;
  if (left_height > right_height) {
    replacement = get_largest_node(which->left);
    if (replacement->left) {
      detach_one_child_node(replacement);
    } else {
      detach_leaf(replacement);
    }
  } else {
    replacement = get_least_node(which->right);
    if (replacement->right) {
      detach_one_child_node(replacement);
    } else {
      detach_leaf(replacement);
    }
  }
  replace(which, replacement);
  return replacement;
}

// leaf does not have any successor, it always return nullptr.
template <typename KeyType, typename ValueType>
TreeNode<KeyType, ValueType>* detach(TreeNode<KeyType, ValueType>* which)
{
  assert(which);
  if (!(which->left) && !(which->right)) {
    detach_leaf(which);
    return nullptr;
  }
  if (!(which->left) || !(which->right)) {
    return detach_one_child_node(which);
  }
  return detach_two_child_node(which);
}

template<typename KeyType, typename ValueType>
TreeNode<KeyType, ValueType>* left_rotate(TreeNode<KeyType, ValueType>* target)
{
  assert(target);
  assert(target->right);
  TreeNode<KeyType, ValueType>* node_to_be_lifted = target->right;
  target->right = node_to_be_lifted->left;
  if (target->right) {
    target->right->parent = target;
  }
  node_to_be_lifted->left = target;
  node_to_be_lifted->parent = target->parent;
  target->parent = node_to_be_lifted;
  if (node_to_be_lifted->parent) {
    if (node_to_be_lifted->parent->left == target) {
      node_to_be_lifted->parent->left = node_to_be_lifted;
    }
    // Never use else even though it is faster, In my opinion
    if (node_to_be_lifted->parent->right == target) {
      node_to_be_lifted->parent->right = node_to_be_lifted;
    }
  }
  return node_to_be_lifted;
}

template<typename KeyType, typename ValueType>
TreeNode<KeyType, ValueType>* right_rotate(TreeNode<KeyType, ValueType>* target)
{
  assert(target);
  assert(target->left);
  TreeNode<KeyType, ValueType>* node_to_be_lifted = target->left;
  target->left = node_to_be_lifted->right;
  if (target->left) {
    target->left->parent = target;
  }
  node_to_be_lifted->right = target;
  node_to_be_lifted->parent = target->parent;
  target->parent = node_to_be_lifted;
  if (node_to_be_lifted->parent) {
    if (node_to_be_lifted->parent->left == target) {
      node_to_be_lifted->parent->left = node_to_be_lifted;
    }
    if (node_to_be_lifted->parent->right == target) {
      node_to_be_lifted->parent->right = node_to_be_lifted;
    }
  }
  return node_to_be_lifted;
}

}
}

#endif //ALGORITHM_DATA_STRUCTURE_TREE_NODE_H
