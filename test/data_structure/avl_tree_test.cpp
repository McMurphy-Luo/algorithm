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

TEST(AVLTreeTest, MapOperationTest) {
  AVLTree<string, string, less<string>> tree;
  ASSERT_EQ(tree.Size(), 0);
  tree.Put("1", "I am 1 string!");
  ASSERT_EQ(tree.Size(), 1);
  shared_ptr<string> holder = tree.Find("1");
  ASSERT_TRUE(holder);
  EXPECT_STREQ(holder->c_str(), "I am 1 string!");
  holder = tree.Remove("0");
  ASSERT_FALSE(holder);
  holder = tree.Remove("1");
  ASSERT_TRUE(holder);
  EXPECT_STREQ(holder->c_str(), "I am 1 string!");
  ASSERT_EQ(tree.Size(), 0);
  tree.Put("1", "I am 1 string!");
  holder = tree.Find("2");
  ASSERT_FALSE(holder);
  tree.Put(string("a"), string("I am a string!"));
  ASSERT_EQ(tree.Size(), 2);
  holder = tree.Find("a");
  ASSERT_TRUE(holder);
  EXPECT_STREQ(holder->c_str(), "I am a string!");
  tree.Put(string("3"), string("I am 3 string!"));
  ASSERT_EQ(tree.Size(), 3);
  holder = tree.Remove("1");
  ASSERT_EQ(tree.Size(), 2);
  EXPECT_STREQ(holder->c_str(), "I am 1 string!");
  holder = tree.Remove("not exists");
  ASSERT_EQ(tree.Size(), 2);
  ASSERT_FALSE(holder);
  holder = tree.Find("1");
  ASSERT_FALSE(holder);
  holder = tree.Find("3");
  ASSERT_TRUE(holder);
  EXPECT_STREQ(holder->c_str(), "I am 3 string!");
  AVLTree<string, string, less<string>> tree2 = tree;
  size_t origin_size = tree2.Size();
  tree2.Put("xx", "xx_s");
  ASSERT_EQ(origin_size + 1, tree2.Size());
  holder = tree2.Find("xx");
  ASSERT_TRUE(holder);
  EXPECT_STREQ(holder->c_str(), "xx_s");
  AVLTree<string, string, less<string>> tree3 = tree2;
  tree2.Clear();
  ASSERT_EQ(tree2.Size(), 0);
  ASSERT_EQ(tree3.Size(), origin_size + 1);
  holder = tree3.Remove("xx");
  ASSERT_TRUE(holder);
  EXPECT_STREQ(holder->c_str(), "xx_s");
  tree2 = tree3;
  ASSERT_EQ(tree2.Size(), tree3.Size());
  holder = tree2.Find("xx");
  ASSERT_FALSE(holder);
}

TEST(AVLTreeTest, RamdomAccessTest) {
  AVLTree<string, string, less<string>> the_tree;
  the_tree.Put("1", "1");
  the_tree.Put("5", "5");
  the_tree.Put("2", "2");
  the_tree.Put("1", "1");
  the_tree.Put("99", "99");
  the_tree.Put("6", "6");
  the_tree.Put("3", "3");
  ASSERT_EQ(the_tree.Size(), 6);
  EXPECT_STREQ(the_tree.At(0).first.c_str(), "1");
  EXPECT_STREQ(the_tree.At(5).first.c_str(), "99");
  EXPECT_STREQ(the_tree.At(3).first.c_str(), "5");
}