#include <string>
#include <iostream>
#include <cassert>
#include "data_structure/linked_list.h"


using namespace algorithm;
int main(int argc, char *argv[]){
    LinkedList<std::string> test_l;

    test_l.push(std::string("hello!"));
    assert(test_l.length() == 1);
    test_l.pop();
    assert(test_l.length() == 0);

    test_l.push(std::string("hello"));
    test_l.push(std::string(" "));
    test_l.push(std::string("world!"));
    assert(test_l.length() == 3);
    std::string hello_world = test_l.pop() + test_l.pop() + test_l.pop();

    std::cout << hello_world << std::endl;
}