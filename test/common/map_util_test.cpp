#include <common/macro.h>
#include <common/map_util.h>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cassert>

using std::cin;
using std::cout;
using std::endl;
using std::set;
using std::string;
using std::map;
using std::to_string;
using algorithm::common::differenceTwoSets;
using algorithm::common::intersectionTwoSets;
using algorithm::common::unionTwoSets;
using algorithm::common::keySet;

template <typename T>
string setToString(T target)
{
    string result;
    for (T::const_iterator iterator = target.cbegin(); iterator != target.cend(); ++iterator) {
        result.append(to_string(*iterator));
        result.append(" ");
    }
    result.pop_back();
    return result;
}

template <typename T>
void printSet(T target)
{
    cout << setToString(target);
    cout << endl;
}

int main()
{
    set<int> test_set1;
    test_set1.insert(1);
    test_set1.insert(2);
    test_set1.insert(3);

    set<int> test_set2;
    test_set2.insert(3);
    test_set2.insert(4);
    test_set2.insert(5);

    map<int, int> test_map;
    cout << test_map[1];
    test_map[1] = 1;
    test_map[2] = 2;
    test_map[3] = 3;

    map<int, string> test_map2;
    test_map2[2] = "2";
    test_map2[3] = "3";
    test_map2[4] = "4";

    assert(setToString(test_set1) == "1 2 3");
    assert(setToString(test_set2) == "3 4 5");
    assert(setToString(unionTwoSets(test_set1, test_set2)) == "1 2 3 4 5");
    assert(setToString(differenceTwoSets(test_set1, test_set2)) == "1 2");
    assert(setToString(intersectionTwoSets(test_set1, test_set2)) == "3");

    assert(setToString(keySet(test_map)) == "1 2 3");

    assert(setToString(intersectionTwoSets(keySet(test_map), keySet(test_map2))) == "2 3");

    printSet(differenceTwoSets(keySet(test_map2), test_set2));

    cin.get();
}