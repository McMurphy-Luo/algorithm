#include "debug_stream.h"
#include <cinttypes>
#include <locale>
#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#else
#include <iostream>
#endif

using namespace algorithm::common;

DebugStream::DebugStream()
    :buf_()
{
    
}

DebugStream::DebugStream(const DebugStream& to)
    :buf_(to.buf_) // wstring.operator=
{
    
}

DebugStream& DebugStream::operator=(const DebugStream& rhs)
{
    if (&rhs == this)
    {
        return;
    }
    buf_ = rhs.buf_; // wstring.operator=
    return *this;
}

DebugStream::~DebugStream()
{
    flush();
}

void DebugStream::flush()
{
#if defined(_WIN32) || defined(_WIN64)
    OutputDebugStringW(buf_.c_str());
#else
    wcout << buf_;
#endif
    buf_.clear();
}

DebugStream& DebugStream::operator<<(int32_t what)
{
    buf_ += what;
    return *this;
}

DebugStream& DebugStream::operator<<(int64_t what)
{
    buf_ += what;
    return *this;
}

DebugStream& DebugStream::operator<<(double what)
{
    buf_ += what;
    return *this;
}

DebugStream& DebugStream::operator<<(const std::wstring& what)
{
    buf_ += what;
    return *this;
}

DebugStream& DebugStream::operator<<(std::ostream& (*endl)(std::ostream&)){
    buf_.push_back(L'\n');
    return *this;
}