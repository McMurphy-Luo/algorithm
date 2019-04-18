#include <string>
#include <iostream>
#include <cassert>
#include <gtest/gtest.h>
#include <data_structure/linked_list.h>
#include <data_structure/array_list.h>

using namespace algorithm;

using algorithm::data_structure::ArrayList;
using algorithm::data_structure::LinkedList;

template<typename T>
void test_list_1(T& list){
    list.add(std::string("hello!"));
    assert(list.size() == 1);
    list.clear();
    assert(list.size() == 0);
    list.add(std::string("hello"));
    list.add(std::string(" "));
    list.add(std::string("world!"));
    assert(list.size() == 3);
    std::string hello_world = list[0] + list[1] + list.get(2);
    assert(hello_world == std::string("hello world!"));
}

template<typename T>
void test_list_2(T& list){
    list.insert(std::string("world"), 0);
    assert(list.size() == 1);
    list.insert(std::string("hello"), 0);
    list.insert(std::string(" "), 1);
    assert(list.size() == 3);
    auto list_2 = list;
    assert(list_2.size() == 3);
    list_2.remove(1);
    assert(list_2.size() == 2);
    assert(list_2[0] + list_2.get(1) == std::string("helloworld"));
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