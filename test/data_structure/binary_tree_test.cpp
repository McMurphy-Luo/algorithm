//
// Created by luojiayi on 5/24/17.
//
#include <string>
#include <iostream>
#include <memory>
#include <cassert>
#include <data_structure/binary_tree.h>
#include <gtest/gtest.h>

using std::string;
using std::shared_ptr;
using algorithm::data_structure::BinaryTree;

int Comparator(const string& lhs, const string& rhs){
    if (lhs < rhs){
        return -1;
    }
    if (lhs > rhs){
        return 1;
    }
    return 0;
};

TEST(BinaryTreeTest, BasicTest) {
  BinaryTree<string, string, Comparator> tree;
  ASSERT_EQ(tree.size(), 0) << "The default constructed tree should be empty";
  tree.put("1", "I am 1 string!");
  ASSERT_EQ(tree.size(), 1) << "After put one string the tree size should be 1";
  shared_ptr<string> holder;
  holder.reset(tree.find("1"));
  assert(*holder == "I am 1 string!");
  holder.reset(tree.find("2"));
  assert(!holder);
  tree.put(string("a"), string("I am a string!"));
  holder.reset(tree.find("a"));
  assert(*holder == "I am a string!");
  tree.put(string("3"), string("I am 3 string!"));
  holder.reset(tree.remove("1"));
  assert(*holder == "I am 1 string!");
  holder.reset(tree.remove("not exists"));
  assert(!holder);
  holder.reset(tree.find("1"));
  assert(!holder);
  holder.reset(tree.find("3"));
  assert(*holder == "I am 3 string!");


  BinaryTree<string, string, Comparator> tree2 = tree;
  algorithm::data_structure::size_type origin_size = tree2.size();
  tree2.put("xx", "xx_s");
  assert(origin_size + 1 == tree2.size());
  holder.reset(tree2.find("xx"));
  assert(*holder == "xx_s");
  BinaryTree<string, string, Comparator> tree3 = tree2;
  tree2.clear();
  assert(tree3.size() == origin_size + 1);
  holder.reset(tree3.remove("xx"));
  assert(*holder == "xx_s");
}
