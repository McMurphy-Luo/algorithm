#include <string>
#include <iostream>
#include <cassert>
#include "data_structure/linked_list.h"
using namespace algorithm;

void test_list_1(){
    LinkedList<std::string> test_l;

    test_l.add(std::string("hello!"));
    assert(test_l.size() == 1);
    test_l.clear();
    assert(test_l.size() == 0);


    test_l.add(std::string("hello"));
    test_l.add(std::string(" "));
    test_l.add(std::string("world!"));
    assert(test_l.size() == 3);
    std::string hello_world = test_l[0] + test_l[1] + test_l.get(2);
    assert(hello_world == std::string("hello world!"));
}



void test_list_2(){
    LinkedList<std::string> test_l;
    test_l.insert(std::string("world"), 0);
    test_l.insert(std::string("hello"), 0);
    test_l.insert(std::string(" "), 1);
    assert(test_l.size() == 3);
    auto test_l_2 = test_l;
    test_l_2.remove(1);
    assert(test_l_2.size() == 2);
    std::cout << test_l_2[0] << std::endl;
    std::cout << test_l_2[1] << std::endl;
//    std::string result = test_l_2[0] + test_l_2[1];
//    assert(result == std::string("helloworld"));
}

int main(int argc, char *argv[]){
    test_list_1();
    test_list_2();
    std::cout << "hello world, test passed!" << std::endl;
}