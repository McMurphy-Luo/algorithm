#include <string>
#include <iostream>
#include <cassert>
#include <gtest/gtest.h>
#include <data_structure/linked_list.h>
#include <data_structure/array_list.h>

using algorithm::data_structure::ArrayList;
using algorithm::data_structure::LinkedList;
using std::string;

template<typename T>
void test_list_1(T& list){
  list.add(std::string("hello!"));
  ASSERT_EQ(list.size(), 1);
  list.clear();
  ASSERT_EQ(list.size(), 0);
  list.add(std::string("hello"));
  list.add(std::string(" "));
  list.add(std::string("world!"));
  ASSERT_EQ(list.size(), 3);
  std::string hello_world = list[0] + list[1] + list.get(2);
  EXPECT_STREQ(hello_world.c_str(), "hello world!");
}

template<typename T>
void test_list_2(T& list){
  list.insert(std::string("world"), 0);
  ASSERT_EQ(list.size(), 1);
  list.insert(std::string("hello"), 0);
  list.insert(std::string(" "), 1);
  ASSERT_EQ(list.size(), 3);
  T list_2 = list;
  ASSERT_EQ(list_2.size(), 3);
  list_2.remove(1);
  ASSERT_EQ(list_2.size(), 2);
  string test_string_from_list = list_2[0] + list_2.get(1);
  EXPECT_STREQ(test_string_from_list.c_str(), "helloworld");
}

TEST(ListTest, TestTheArrayList) {
  ArrayList<std::string> array_l1, array_l2;
  test_list_1(array_l1);
  test_list_2(array_l2);
}

TEST(ListTest, TestTheLinkedList) {
  LinkedList<std::string> linked_l1, linked_l2;
  test_list_1(linked_l1);
  test_list_2(linked_l2);
}