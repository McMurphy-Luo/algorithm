#ifndef ALGORITHM_COMMON_BUFFER_UTIL
#define ALGORITHM_COMMON_BUFFER_UTIL

#include <string>

namespace algorithm
{
    namespace common
    {
        std::string dumpBufferAsHexString(char *buf, std::size_t buf_size);

        std::string dumpBufferAsBinaryString(char *buf, std::size_t buf_size);
    }
}

#endif // ALGORITHM_COMMON_BUFFER_UTIL
