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
using std::shared_ptr;
using std::weak_ptr;
using std::enable_shared_from_this;
using std::make_shared;

class Test : public enable_shared_from_this<Test>
{
public:
    Test(int a)
        :a_(a)
    {

    }

    int getA() { return a_; }

    void setA(int value) { a_ = value; }

private:
    int a_;
};

int main(int argc, char* argv[]) {
    char *test_string = "𐐀";
    wchar_t *test_string2 = L"𐐀";
    shared_ptr<Test> t = make_shared<Test>(5);
    weak_ptr<Test> t2(nullptr);
    int wide_string_length = MultiByteToWideChar(CP_ACP, 0, test_string, -1, nullptr, 0);
    cout << wide_string_length << endl;
    cout << wcslen(test_string2) << endl;
    Test t(1);
    shared_ptr<Test> t2 = make_shared<Test>(2);
    t.shared_from_this();
    cin.get();
}
