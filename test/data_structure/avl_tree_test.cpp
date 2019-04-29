//
// Created by luojiayi on 5/24/17.
//
#include <string>
#include <iostream>
#include <memory>
#include <cassert>
#include <data_structure/avl_tree.h>
#include <gtest/gtest.h>

using std::string;
using std::shared_ptr;
using algorithm::data_structure::AVLTree;

TEST(BinaryTreeTest, BasicTest) {
  AVLTree<string, string, std::less<string>> tree;
  ASSERT_EQ(tree.size(), 0) << "The default constructed tree should be empty";

  std::cout << "here1" << std::endl;

  tree.put("1", "I am 1 string!");
  ASSERT_EQ(tree.size(), 1) << "After put one string the tree size should be 1";
  shared_ptr<string> holder;
  holder.reset(tree.find("1"));
  ASSERT_STREQ(holder->c_str(), "I am 1 string!");
  holder.reset(tree.find("2"));
  ASSERT_TRUE(!holder);
  std::cout << "here2" << std::endl;
  tree.put(string("a"), string("I am a string!"));
  std::cout << "here3" << std::endl;
  holder.reset(tree.find("a"));
  std::cout << "here4" << std::endl;
  ASSERT_STREQ(holder->c_str(), "I am a string!");
  std::cout << "here5" << std::endl;
  tree.put(string("3"), string("I am 3 string!"));
  std::cout << "here6" << std::endl;
  holder.reset(tree.remove("1"));
  std::cout << "here7" << std::endl;
  assert(*holder == "I am 1 string!");
  std::cout << "here8" << std::endl;
  holder.reset(tree.remove("not exists"));
  std::cout << "here9" << std::endl;
  assert(!holder);
  std::cout << "here3" << std::endl;
  holder.reset(tree.find("1"));
  assert(!holder);
  holder.reset(tree.find("3"));
  assert(*holder == "I am 3 string!");
  std::cout << "here4" << std::endl;
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
