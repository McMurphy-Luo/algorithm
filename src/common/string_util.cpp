#include "../config.h"
#include "./string_util.h"
#include <cassert>
#ifdef ALGORITHM_WINDOWS
#include <Windows.h>
#else
#include <codecvt>
#endif

std::wstring algorithm::common::u8StringToWString(const std::string& utf8_string)
{
#ifdef ALGORITHM_WINDOWS
    std::size_t wchar_buf_size_required = MultiByteToWideChar(CP_UTF8, 0, utf8_string.c_str(), -1, nullptr, 0);
    wchar_t* buf = new wchar_t[wchar_buf_size_required];
    assert(MultiByteToWideChar(CP_UTF8, 0, utf8_string.c_str(), -1, buf, wchar_buf_size_required) == wchar_buf_size_required);
    std::wstring result(buf);
    delete[] buf;
    return result;
#else
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    return converter.from_bytes(utf8_string);
#endif
}

std::string algorithm::common::wStringToU8String(const std::wstring& wstring)
{
#ifdef ALGORITHM_WINDOWS
    std::size_t char_buf_size_required = WideCharToMultiByte(CP_UTF8, 0, wstring.c_str(), -1, nullptr, 0, nullptr, nullptr);
    char* buf = new char[char_buf_size_required];
    assert(WideCharToMultiByte(CP_UTF8, 0, wstring.c_str(), -1, buf, char_buf_size_required, nullptr, nullptr));
    std::string result(buf);
    delete[] buf;
    return result;
#else
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    return converter.to_bytes(wstring);
#endif
}

std::size_t algorithm::common::u8CharactorCount(const std::string& utf8_string)
{
    return u8StringToWString(utf8_string).length();
}