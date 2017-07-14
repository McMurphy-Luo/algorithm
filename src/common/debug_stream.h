#ifndef ALGORITHM_COMMON_DEBUG_STREAM
#define ALGORITHM_COMMON_DEBUG_STREAM

#include <string>
#include <cstdint>
#include <iostream>

namespace algorithm
{
    namespace common
    {
        class DebugStream
        {
        public:
            DebugStream();

            DebugStream(const DebugStream& to);

            DebugStream& operator=(const DebugStream& rhs);

            ~DebugStream();

            void flush();
            
            DebugStream& operator<<(std::string what);

            DebugStream& operator<<(std::wstring what);

            DebugStream& operator<<(int32_t what);

            DebugStream& operator<<(int64_t what);

            DebugStream& operator<<(double what);

        private:
            std::wstring buf_;
        };
    }
}

#endif // ALGORIHTM_COMMON_DEBUG_STREAM