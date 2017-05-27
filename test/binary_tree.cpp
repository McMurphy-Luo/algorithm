//
// Created by luojiayi on 5/24/17.
//
#include "data_structure/binary_tree.h"

#include <string>
#include <iostream>

int string_comparator(const std::string& left, const std::string& right){
    if (left > right){
        return 1;
    }
    if (left < right){
        return -1;
    }
    return 0;
}

using namespace std;

int main(){
    algorithm::BinaryTree<string, string, string_comparator> tree;
    tree.put(string("1"), string("I am 1 string!"));
    tree.put(string("a"), string("I am a string!"));
    tree.put(string("3"), string("I am 1 string!"));
    tree.put(string("asdfasdfqe"), string("I am asdfasdfqe string!"));
    tree.put(string("asdfa"), string("I am asdfa string!"));
    tree.put(string("123123asdfa"), string("I am 123123asdfa string!"));


    string* test = tree.find("asdfa");
    cout << *test << endl;
    delete test;
    test = tree.find("2");
    cout << test << endl;
}