#include <string>
#include <iostream>
#include <cassert>
#include "data_structure/linked_list.h"
#include "data_structure/array_list.h"
using namespace algorithm;
using namespace std;

template<typename T>
void test_list_1(const T& list){
    list.add(std::string("hello!"));
    assert(list.size() == 1);
    list.clear();
    assert(list.size() == 0);
    list.add(std::string("hello"));
    list.add(std::string(" "));
    list.add(std::string("world!"));
    assert(list.size() == 3);
    std::cout << list.toString() << std::endl;
    std::string hello_world = list[0] + list[1] + list.get(2);
    assert(hello_world == std::string("hello world!"));
}

template<typename T>
void test_list_2(const T& list){
    list.insert(std::string("world"), 0);
    std::cout << list.toString() << std::endl;
    assert(list.size() == 1);
    list.insert(std::string("hello"), 0);
    list.insert(std::string(" "), 1);
    std::cout << list.toString() << std::endl;
    assert(list.size() == 3);
    auto list_2 = list;
    std::cout << list_2.toString() << std::endl;
    assert(list_2.size() == 3);
    list_2.remove(1);
    assert(list_2.size() == 2);
    std::cout << list_2[0] << std::endl;
    std::cout << list_2[1] << std::endl;
//    std::string result = test_l_2[0] + test_l_2[1];
//    assert(result == std::string("helloworld"));
}

int main(){
    LinkedList<std::string> linked_l;
    ArrayList<std::string> array_l;
    test_list_1(linked_l);
    test_list_2(linked_l);
    test_list_1(array_l);
    test_list_2(array_l);
    std::cout << "hello world, test passed!" << std::endl;
}