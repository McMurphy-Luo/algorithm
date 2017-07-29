#ifndef ALGORITHM_COMMON_DEBUG_STREAM
#define ALGORITHM_COMMON_DEBUG_STREAM

#include <string>
#include <cstdint>

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

            DebugStream& operator<<(const std::wstring& what);

            DebugStream& operator<<(int32_t what);

            DebugStream& operator<<(int64_t what);

            DebugStream& operator<<(double what);

            DebugStream& DebugStream::operator<<(std::ostream& (*endl)(std::ostream&));

        private:
            std::wstring buf_;
        };
    }
}

#endif // ALGORIHTM_COMMON_DEBUG_STREAM