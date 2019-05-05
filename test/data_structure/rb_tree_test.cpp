#include <string>
#include <algorithm>
#include <gtest/gtest.h>
#include <data_structure/rb_tree.h>


using std::string;
using std::less;
using algorithm::data_structure::RBTree;


TEST(RedBlackTreeTest, BasicTest) {
  RBTree<string, string, less<string>> the_tree;

  ASSERT_TRUE(the_tree.Empty());
  ASSERT_EQ(the_tree.Size(), 0);
  the_tree.Put("1", "1");
  ASSERT_EQ(the_tree.Size(), 1);
}