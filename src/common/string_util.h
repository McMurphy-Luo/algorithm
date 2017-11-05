#ifndef ALGORITHM_COMMON_STRING_UTIL
#define ALGORITHM_COMMON_STRING_UTIL

#include <string>

namespace algorithm
{
    namespace common
    {
        std::wstring u8StringToWString(const std::string& utf8_string);

        std::string wStringToU8String(const std::wstring& wstring);

        std::size_t u8CharactorCount(const std::string& utf8_string);
    }
}
#endif //ALGORITHM_COMMON_STRING_UTIL
