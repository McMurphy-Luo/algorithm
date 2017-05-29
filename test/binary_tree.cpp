//
// Created by luojiayi on 5/24/17.
//
#include <string>
#include <iostream>
#include <memory>
#include <cassert>
#include "data_structure/binary_tree.h"

using namespace std;
using namespace algorithm;

int Comparator(const string& lhs, const string& rhs){
    if (lhs < rhs){
        return -1;
    }
    if (lhs > rhs){
        return 1;
    }
    return 0;
};

template <typename T>
void test1(T& the_tree){
    assert(the_tree.size() == 0);
    shared_ptr<string> holder;
    the_tree.put("1", "I am 1 string!");
    assert(the_tree.size() == 1);
    holder.reset(the_tree.find("1"));
    assert(*holder == "I am 1 string!");
    holder.reset(the_tree.find("2"));
    assert(!holder);
    the_tree.put(string("a"), string("I am a string!"));
    holder.reset(the_tree.find("a"));
    assert( *holder == "I am a string!" );
    the_tree.put(string("3"), string("I am 3 string!"));
    holder.reset(the_tree.remove("1"));
    assert(*holder == "I am 1 string!");
    holder.reset(the_tree.remove("not exists"));
    assert(!holder);
    holder.reset(the_tree.find("1"));
    assert(!holder);
    holder.reset(the_tree.find("3"));
    assert(*holder == "I am 3 string!");
}

template <typename T>
void test2(T& the_tree){
    typename T::size_type origin_size = the_tree.size();
    the_tree.put("xx", "xx_s");
    assert(origin_size + 1 == the_tree.size());
    shared_ptr<string> holder(the_tree.find("xx"));
    assert(*holder == "xx_s");
    T tree2 = the_tree;
    the_tree.clear();
    assert(tree2.size() == origin_size + 1);
    holder.reset(tree2.remove("xx"));
    assert(*holder == "xx_s");
}

int main(){
    BinaryTree<string, string, Comparator> tree;
    test1(tree);
    BinaryTree<string, string, Comparator> tree2 = tree;
    test2(tree2);
    cout << "All BinaryTree test passed!" << endl;
}