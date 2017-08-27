//
// Created by luojiayi on 5/18/17.
//
#include <memory>
#include <iostream>
#include <cassert>
#include <Windows.h>

using namespace std;

int main(int argc, char* argv[]){
    assert(false);
    size_t wide_string_buf_required = MultiByteToWideChar(CP_UTF8, 0, u8"good", -1, nullptr, 0);

    cout << wide_string_buf_required;
    cin.get();
}