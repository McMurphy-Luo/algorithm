#ifndef ALGORITHM_COMMON_MAP_UTIL_H
#define ALGORITHM_COMMON_MAP_UTIL_H

#include <cassert>
#include <set>
#include <map>

namespace algorithm
{
    namespace common
    {
        template<typename T>
        T unionTwoSets(const T &set1, const T &set2)
        {
            T result = set1;
            for (T::const_iterator iterator = set2.cbegin(); iterator != set2.end(); ++iterator) {
                std::pair<T::const_iterator, bool> insert_result = result.insert(*iterator);
                
                assert(
                    insert_result.second
                    ||
                    (
                        !result.key_comp()(*(insert_result.first), *iterator)
                        &&
                        !result.key_comp()(*iterator, *(insert_result.first))
                    )
                );
            }
            return result;
        }

        template<typename T>
        T differenceTwoSets(const T &set1, const T &set2)
        {
            T result = set1;
            for (T::const_iterator iterator = set2.cbegin(); iterator != set2.end(); ++iterator) {
                T::size_type item_removed = result.erase(*iterator);
                assert(item_removed == 1 || item_removed == 0);
            }
            return result;
        }

        template<typename T>
        T intersectionTwoSets(const T &set1, const T &set2)
        {
            T result;
            for (T::const_iterator iterator = set1.cbegin(); iterator != set1.end(); ++iterator) {
                if (set2.find(*iterator) != set2.end()) {
                    std::pair<T::const_iterator, bool> insert_result = result.insert(*iterator);
                    assert(
                        insert_result.second
                        ||
                        (
                            !result.key_comp()(*(insert_result.first), *iterator)
                            &&
                            !result.key_comp()(*iterator, *(insert_result.first))
                        )
                    );
                }
            }
            return result;
        }


        template<
            class Key,
            class T,
            class Compare = std::less<Key>,
            class Allocator = std::allocator<std::pair<const Key, T>>
        >
        std::set<Key, Compare> keySet(const std::map<Key, T, Compare, Allocator> &the_map)
        {
            std::set<Key, Compare> result;
            for (std::map<Key, T, Compare, Allocator>::const_iterator iterator = the_map.cbegin(); iterator != the_map.cend(); ++iterator) {
                result.insert(iterator->first);
            }
            return result;
        }
    }
}

#endif // ALGORITHM_COMMON_MAP_UTIL_H