#include <string>
#include <algorithm>
#include <gtest/gtest.h>
#include <data_structure/rb_tree.h>

using std::shared_ptr;
using std::string;
using std::less;
using algorithm::data_structure::RBTree;


TEST(RedBlackTreeTest, BasicTreeOperationTest) {
  RBTree<string, string, less<string>> the_tree;
  ASSERT_TRUE(the_tree.Empty());
  ASSERT_EQ(the_tree.Size(), 0);
  the_tree.Put("1", "1");
  ASSERT_EQ(the_tree.Size(), 1);
  ASSERT_FALSE(the_tree.Empty());
  the_tree.Put("2", "2");
  the_tree.Put("3", "3");
  the_tree.Put("4", "4");
  the_tree.Put("5", "5");
  the_tree.Put("6", "6");
  the_tree.Put("7", "7");
  the_tree.Put("8", "8");
  ASSERT_EQ(the_tree.Size(), 8);
  the_tree.Put("0", "0");
  shared_ptr<string> result = the_tree.Find("11");
  EXPECT_FALSE(result);
  result = the_tree.Find("2");
  ASSERT_TRUE(result);
  EXPECT_EQ(*result, "2");
  result = the_tree.Find("3");
  ASSERT_TRUE(result);
  EXPECT_EQ(*result, "3");
  the_tree.Put("3", "33");
  EXPECT_EQ(the_tree.Size(), 9);
  result = the_tree.Find("3");
  ASSERT_TRUE(result);
  EXPECT_EQ(*result, "33");
  the_tree.Clear();
  EXPECT_TRUE(the_tree.Empty());
  EXPECT_EQ(the_tree.Size(), 0);
}

TEST(RedBlackTreeTest, SpecialClassMemberTest) {
  RBTree<string, string, less<string>> the_tree;
  ASSERT_TRUE(the_tree.Empty());
  the_tree.Put("0", "0");
  the_tree.Put("1", "1");
  the_tree.Put("2", "2");
  the_tree.Put("3", "3");
  the_tree.Put("4", "4");
  the_tree.Put("5", "5");
  the_tree.Put("6", "6");
  the_tree.Put("7", "7");
  the_tree.Put("8", "8");
  RBTree<string, string, less<string>> tree_copy = the_tree;
  ASSERT_EQ(tree_copy.Size(), 9);

  RBTree<string, string, less<string>> tree_assign;
  tree_assign.Put("0", "00");
  tree_assign.Put("3", "33");
}
