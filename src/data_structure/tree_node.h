#ifndef ALGORITHM_DATA_STRUCTURE_TREE_NODE_H
#define ALGORITHM_DATA_STRUCTURE_TREE_NODE_H

#include <cstddef>
#include <cassert>

namespace algorithm {
    typedef int size_type;

    typedef enum class NodeColor {
        red,
        black
    } node_color;

    /*
     * The only one node type for avl tree, red black tree, trivial binary tree.
     * In avl tree and trivial binary tree, node color is always black.
     */
    template <typename KeyType, typename ValueType>
    struct TreeNode {
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
        ): key(key), value(value), parent(parent), left(left), right(right), color(color){}
        key_type key;
        value_type value;
        node *parent;
        node *left;
        node *right;
        node_color color;
    };

    template<typename KeyType, typename ValueType>
    size_type size(const TreeNode<KeyType, ValueType>* which) {    // post order traversal
        if (!which) // empty node size is 0
        {
            return 0;
        }
        return size(which->left) + size(which->right) + 1;
    }

    template<typename KeyType, typename ValueType>
    size_type height(const TreeNode<KeyType, ValueType>* which) {  // post order traversal
        if (!which) // empty node height is 0
        {
            return 0;
        }
        size_type left_sub_tree_height = height(which->left);
        size_type right_sub_tree_height = height(which->right);
        return 1 + (
            right_sub_tree_height > left_sub_tree_height ? right_sub_tree_height : left_sub_tree_height
            );
    }

    template <typename KeyType, typename ValueType>
    TreeNode<KeyType, ValueType>* get_least_node(TreeNode<KeyType, ValueType> *from) {
        if (!from)
        {
            return nullptr;
        }
        while (from->left) {
            from = from->left;
        }
        return from;
    }

    template <typename KeyType, typename ValueType>
    TreeNode<KeyType, ValueType>* get_largest_node(TreeNode<KeyType, ValueType>* from) {
        if (!from)
        {
            return nullptr;
        }
        while (from->right) {
            from = from->right;
        }
        return from;
    }

    // leaf does not have any successor, it always return nullptr.
    template <typename KeyType, typename ValueType>
    TreeNode<KeyType, ValueType>* detach(TreeNode<KeyType, ValueType>* which) {
        if (!which)
        {
            return nullptr;
        }
        // from now the "which" has two child
        size_type left_child_height = height(which->left);
        size_type right_child_height = height(which->right);

        TreeNode<KeyType, ValueType>* node_to_be_lifted;
        if (left_child_height > right_child_height){
            node_to_be_lifted = get_largest_node(which->left);
            assert(node_to_be_lifted);
            assert(!(node_to_be_lifted->right));
        } else {
            node_to_be_lifted = get_least_node(which->right);
        }
        detach(node_to_be_lifted);
        if (node_to_be_lifted){
            node_to_be_lifted->right = which->right;
            node_to_be_lifted->left = which->left;
            node_to_be_lifted->parent = which->parent;
        }

        if (which->parent){
            if (which->parent->left == which){
                which->parent->left = node_to_be_lifted;
            }
            if (which->parent->right == which){
                which->parent->right = node_to_be_lifted;
            }
        }
        return node_to_be_lifted;
    }

    template<typename KeyType, typename ValueType>
    void left_rotate(TreeNode<KeyType, ValueType>* target){
        assert(target);
        assert(target->right);
        TreeNode<KeyType, ValueType>* node_to_be_lifted = target->right;
        target->right = node_to_be_lifted->left;
        target->right->parent = target;
        node_to_be_lifted->left = target;
        node_to_be_lifted->parent = target->parent;
        target->parent = node_to_be_lifted;
    }

    template<typename KeyType, typename ValueType>
    void right_rotate(TreeNode<KeyType, ValueType>* target, TreeNode<KeyType, ValueType>* target_parent)
    {
        assert(target);
        assert(target->left);
        TreeNode<KeyType, ValueType>* node_to_be_lifted = target->left;
        target->left = node_to_be_lifted->right;
        target->left->parent = target;
        node_to_be_lifted->right = target;
        node_to_be_lifted->parent = target->parent;
        target->parent = node_to_be_lifted;
    }
}

#endif //ALGORITHM_DATA_STRUCTURE_TREE_NODE_H
