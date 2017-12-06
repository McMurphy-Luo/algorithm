#ifndef ALGORITHM_COMMON_MAP_UTIL_H
#define ALGORITHM_COMMON_MAP_UTIL_H

#include <set>

namespace algorithm
{
    namespace common
    {
        template<typename T>
        T unionTwoSets(const T &set1, const T &set2)
        {
            T result;
            for (T::const_iterator iterator = set1.cbegin(); iterator != set1.end(); ++iterator) {
                result.insert(*iterator);
            }
            for (T::const_iterator iterator = set2.cbegin(); iterator != set2.end(); ++iterator) {
                result.insert(*iterator);
            }
            return result;
        }

        template<typename T>
        T differenceTwoSets(const T &set1, const T &set2)
        {
            T result;
            return result;
        }

        template<typename T>
        T intersectionTwoSets(const T &set1, const T &set2)
        {
            T result;
            return result;
        }
    }
}

#endif // ALGORITHM_COMMON_MAP_UTIL_H