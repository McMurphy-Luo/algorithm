#include "debug_stream.h"
#include <cstdio>
#include <cinttypes>
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
    cerr << buf_;
#endif
    buf_.clear();
}

DebugStream& DebugStream::operator<<(int32_t what)
{
    buf_ += std::to_wstring(what);
    return *this;
}

DebugStream& DebugStream::operator<<(int64_t what)
{
    buf_ += std::to_wstring(what);
    return *this;
}

DebugStream& DebugStream::operator<<(double what)
{
    buf_ += std::to_wstring(what);
    return *this;
}

DebugStream& DebugStream::operator<<(std::string what)
{
    
}

DebugStream& DebugStream::operator<<(std::wstring what)
{
    return *this;
}