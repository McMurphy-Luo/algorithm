#include <string>
#include <iostream>
#include <cassert>
#include "data_structure/linked_list.h"


using namespace algorithm;
int main(int argc, char *argv[]){
    LinkedList<std::string> test_l;

    test_l.add(std::string("hello!"));
    assert(test_l.size() == 1);
    test_l.clear();
    assert(test_l.size() == 0);

    test_l.add(std::string("hello"));
    test_l.add(std::string(" "));
    test_l.add(std::string("world!"));
    assert(test_l.size() == 3);
    std::string hello_world = test_l.get(0) + test_l.get(1) + test_l.get(2);

    std::cout << hello_world << std::endl;
}