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

set<int> union_test(const set<int> &set1, const set<int> &set2)
{
    set<int> result;
    for (set<int>::const_iterator iterator = set1.cbegin(); iterator != set1.end(); ++iterator) {
        std::pair<set<int>::const_iterator, bool> insert_result = result.insert(*iterator);
        cout << *insert_result.first;
        cout << (insert_result.second ? " true" : " false");
        cout << endl;
    }
    for (set<int>::const_iterator iterator = set2.cbegin(); iterator != set2.end(); ++iterator) {
        std::pair<set<int>::const_iterator, bool> insert_result = result.insert(*iterator);
        cout << *insert_result.first;
        cout << (insert_result.second ? " true" : " false");
        cout << endl;
    }
    return result;
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

    assert(setToString(test_set1) == string("1 2 3"));
    assert(setToString(test_set2) == string("3 4 5"));
    assert(setToString(union_test(test_set1, test_set2)) == string("1 2 3 4 5"));

    cin.get();
}