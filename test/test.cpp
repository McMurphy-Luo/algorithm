//
// Created by luojiayi on 5/18/17.
//
#include <memory>
#include <iostream>
#include <cassert>
#include <Windows.h>
#include "common/buffer_util.h"

using algorithm::common::dumpBufferAsHexString;

int main(int argc, char* argv[]){
    int a = -1;
    std::cout << dumpBufferAsHexString((char*)&a, 4) << std::endl;
    std::cin.get();
}
