#ifndef ALGORITHM_DATA_STRUCTURE_TREE_NODE_H
#define ALGORITHM_DATA_STRUCTURE_TREE_NODE_H

#include <cstddef>
#include <cassert>

namespace algorithm {
    typedef std::size_t size_type;

    typedef enum class NodeColor{
        red,
        black
    } node_color;

    template <typename KeyType, typename ValueType>
    struct TreeNode {
        typedef KeyType key_type;
        typedef ValueType value_type;
        TreeNode(
                key_type key,
                value_type value,
                TreeNode<key_type, value_type> *left = nullptr,
                TreeNode<key_type, value_type> *right = nullptr,
                node_color color = node_color::black
        ): key(key), value(value), left(left), right(right), color(color){}
        key_type key;
        value_type value;
        TreeNode<key_type, value_type>* left;
        TreeNode<key_type, value_type>* right;
        node_color color;
    };

    template<typename KeyType, typename ValueType>
    size_type size(const TreeNode<KeyType, ValueType>* which) {    // post order traversal
        assert(which);
        size_type left_sub_tree_size = which->left ? size(which->left) : 0;
        size_type right_sub_tree_size = which->right ? size(which->right) : 0;
        return left_sub_tree_size + right_sub_tree_size + 1;
    };

    template<typename KeyType, typename ValueType>
    size_type height(const TreeNode<KeyType, ValueType>* which) {  // post order traversal
        assert(which);
        size_type left_sub_tree_height = which->left ? height(which->left) : 0;
        size_type right_sub_tree_height = which->right ? height(which->right) : 0;
        return 1 + (
            right_sub_tree_height > left_sub_tree_height ? right_sub_tree_height : left_sub_tree_height
            );
    };

    template <typename KeyType, typename ValueType>
    void get_least_node(TreeNode<KeyType, ValueType> *from, TreeNode<KeyType, ValueType>* from_parent, TreeNode<KeyType, ValueType> **target, TreeNode<KeyType, ValueType> **target_parent) {
        assert(from);
        assert(!from_parent || (from_parent->left == from || from_parent->right == from));
        *target = from;
        *target_parent = from_parent;
        while ((*target)->left) {
            *target_parent = *target;
            *target = (*target)->left;
        }
    };

    template <typename KeyType, typename ValueType>
    void get_largest_node(TreeNode<KeyType, ValueType>* from, TreeNode<KeyType, ValueType>* from_parent, TreeNode<KeyType, ValueType> **target, TreeNode<KeyType, ValueType> **target_parent) {
        assert(from);
        assert(!from_parent || (from_parent->left == from || from_parent->right == from));
        *target = from;
        *target_parent = from_parent;
        while ((*target)->right) {
            *target_parent = *target;
            *target = (*target)->right;
        }
    };

    // leaf does not have any successor, it always return nullptr.
    template <typename KeyType, typename ValueType>
    TreeNode<KeyType, ValueType>* detach_leaf(TreeNode<KeyType, ValueType>* target, TreeNode<KeyType, ValueType>* parent) {
        assert(target);
        assert(target->left == nullptr && target->right == nullptr);
        assert(!parent || target == parent->left || target == parent->right);
        if (!parent) {
            return nullptr;
        }
        if (target == parent->left) {
            parent->left = nullptr;
        }
        if (target == parent->right) {
            parent->right = nullptr;
        }
        return nullptr;
    };

    //detach the target node from the tree, replace the target with the successor of it and return the successor.
    template <typename KeyType, typename ValueType>
    TreeNode<KeyType, ValueType>* detach_one_child_node(TreeNode<KeyType, ValueType>* target, TreeNode<KeyType, ValueType>* parent) {
        assert(target);
        assert((target->left == nullptr && target->right) || (target->left && target->right == nullptr));
        assert(!parent || target == parent->left || target == parent->right);
        TreeNode<KeyType, ValueType>* my_child = target->left ? target->left : target->right;
        target->left = target->right = nullptr;
        if (!parent) { // no parent, target must be root
            return my_child;
        }
        if (target == parent->left) {
            parent->left = my_child;
        }
        if (target == parent->right) {
            parent->right = my_child;
        }
        return my_child;
    };

    //detach the target node from the tree and return the successor of target
    template <typename KeyType, typename ValueType>
    TreeNode<KeyType, ValueType>* detach_two_children_node(TreeNode<KeyType, ValueType>* target, TreeNode<KeyType, ValueType>* parent) {
        assert(target);
        assert(target->left && target->right);
        assert(!parent || target == parent->left || target == parent->right);
        size_type left_child_height = height(target->left);
        size_type right_child_height = height(target->right);

        TreeNode<KeyType, ValueType>* sub_tree_to_be_lifted;
        TreeNode<KeyType, ValueType>* parent_of_sub_tree_to_be_lifted;
        if (left_child_height >= right_child_height) {
            get_largest_node(target->left, target, &sub_tree_to_be_lifted, &parent_of_sub_tree_to_be_lifted);
            assert(!sub_tree_to_be_lifted->right);
        } else {
            get_least_node(target->right, target, &sub_tree_to_be_lifted, &parent_of_sub_tree_to_be_lifted);
            assert(!sub_tree_to_be_lifted->left);
        }

        if (height(sub_tree_to_be_lifted) == 1) {
            detach_leaf(sub_tree_to_be_lifted, parent_of_sub_tree_to_be_lifted);
        } else {
            detach_one_child_node(sub_tree_to_be_lifted, parent_of_sub_tree_to_be_lifted);
        }
        sub_tree_to_be_lifted->left = target->left;
        sub_tree_to_be_lifted->right = target->right;
        target->left = nullptr;
        target->right = nullptr;
        if (parent && parent->left == target) {
            parent->left = sub_tree_to_be_lifted;
        }
        if (parent && parent->right == target) {
            parent->right = sub_tree_to_be_lifted;
        }
        return sub_tree_to_be_lifted;
    };

    template<typename KeyType, typename ValueType>
    void left_rotate(TreeNode<KeyType, ValueType>* target, TreeNode<KeyType, ValueType>* target_parent){

    }

    template<typename KeyType, typename ValueType>
    void right_rotate(TreeNode<KeyType, ValueType>* target, TreeNode<KeyType, ValueType>* target_parent){

    }
}

#endif //ALGORITHM_DATA_STRUCTURE_TREE_NODE_H