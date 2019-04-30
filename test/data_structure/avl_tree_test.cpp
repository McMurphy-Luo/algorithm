//
// Created by luojiayi on 5/24/17.
//
#include <string>
#include <iostream>
#include <memory>
#include <data_structure/avl_tree.h>
#include <gtest/gtest.h>

using std::string;
using std::shared_ptr;
using std::less;
using std::size_t;
using algorithm::data_structure::AVLTree;

TEST(AVLTreeTest, BasicTest) {
  AVLTree<string, string, less<string>> tree;
  ASSERT_EQ(tree.Size(), 0) << "The default constructed tree should be empty";
  tree.Put("1", "I am 1 string!");
  ASSERT_EQ(tree.Size(), 1) << "After put one string the tree size should be 1";
  shared_ptr<string> holder = tree.Find("1");
  ASSERT_TRUE(holder);
  ASSERT_STREQ(holder->c_str(), "I am 1 string!");
  holder = tree.Find("2");
  ASSERT_TRUE(!holder);
  tree.Put(string("a"), string("I am a string!"));
  ASSERT_EQ(tree.Size(), 2);
  holder = tree.Find("a");
  ASSERT_TRUE(holder);
  ASSERT_STREQ(holder->c_str(), "I am a string!");
  tree.Put(string("3"), string("I am 3 string!"));
  ASSERT_EQ(tree.Size(), 3);
  holder = tree.Remove("1");
  ASSERT_EQ(tree.Size(), 2);
  ASSERT_STREQ(holder->c_str(), "I am 1 string!");
  holder = tree.Remove("not exists");
  ASSERT_EQ(tree.Size(), 2);
  ASSERT_TRUE(!holder);
  holder = tree.Find("1");
  ASSERT_TRUE(!holder);
  holder = tree.Find("3");
  ASSERT_TRUE(holder);
  ASSERT_STREQ(holder->c_str(), "I am 3 string!");
  AVLTree<string, string, less<string>> tree2 = tree;
  size_t origin_size = tree2.Size();
  tree2.Put("xx", "xx_s");
  ASSERT_EQ(origin_size + 1, tree2.Size());
  holder = tree2.Find("xx");
  ASSERT_TRUE(holder);
  EXPECT_STREQ(holder->c_str(), "xx_s");
  AVLTree<string, string, less<string>> tree3 = tree2;
  tree2.Clear();
  EXPECT_EQ(tree3.Size(), origin_size + 1);
  holder = tree3.Remove("xx");
  ASSERT_TRUE(holder);
  ASSERT_STREQ(holder->c_str(), "xx_s");
}
