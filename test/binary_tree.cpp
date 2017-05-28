//
// Created by luojiayi on 5/24/17.
//
#include <string>
#include <iostream>
#include <memory>
#include "data_structure/binary_tree.h"

using namespace std;
using namespace algorithm;

int Comparator(const string& lhs, const string& rhs){
//    cout << lhs << endl;
//    cout << rhs << endl;
//    cout << (lhs > rhs ) << endl;
//    cout << (lhs < rhs) << endl;
    if (lhs < rhs){
//        cout << lhs << " less than " << rhs << endl;
        return -1;
    }
    if (lhs > rhs){
//        cout << lhs << " greater than " << rhs << endl;
        return 1;
    }
    return 0;
};

int main(){
//    cout << Comparator("a", "1") << endl;
//    cout << Comparator("a", "3") << endl;
//    cout << Comparator("123123asdfa", "3") << endl;
    BinaryTree<string, string, Comparator> tree;
    tree.put(string("1"), string("I am 1 string!"));
    tree.put(string("a"), string("I am a string!"));
    tree.put(string("3"), string("I am 3 string!"));
    tree.put(string("asdfasdfqe"), string("I am asdfasdfqe string!"));
    tree.put(string("asdfa"), string("I am asdfa string!"));
    tree.put(string("123123asdfa"), string("I am 123123asdfa string!"));
//    tree.remove(string("1"));
//    tree.remove(string("asdfa"));

    shared_ptr<string> test(tree.find("3"));
    cout << test.get() << endl;
    test.reset(tree.find("123123asdfa"));
    cout << test.get() << endl;
}