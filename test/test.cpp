//
// Created by luojiayi on 5/18/17.
//
#include <memory>
#include <iostream>
#include <cassert>
#include <Windows.h>

using std::cout;
using std::cin;
using std::endl;

int main(int argc, char* argv[]) {
    wchar_t *test_string = L"b";
    wchar_t *test_string2 = L"a";

    cout << wcslen(test_string) << endl;
    cout << wcslen(test_string2) << endl;

    cin.get();
}
