//
// Created by luojiayi on 5/24/17.
//
#include <string>
#include <iostream>
#include "data_structure/binary_tree.h"

using namespace std;
using namespace algorithm;

int main(){
    BinaryTree<string, string, [](const std::string& left, const std::string& right) -> int {
        if (left > right){
            return 1;
        }
        if (left < right){
            return -1;
        }
        return 0;
    }> tree;
    tree.put(string("1"), string("I am 1 string!"));
    tree.put(string("a"), string("I am a string!"));
    tree.put(string("3"), string("I am 3 string!"));
    tree.put(string("asdfasdfqe"), string("I am asdfasdfqe string!"));
    tree.put(string("asdfa"), string("I am asdfa string!"));
    tree.put(string("123123asdfa"), string("I am 123123asdfa string!"));


    string* test = tree.find("asdfa");
    cout << *test << endl;
    delete test;
    test = tree.find("2");
    cout << test << endl;
}