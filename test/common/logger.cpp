#include "./macro.h" // config macro staff
#include "./logger.h"
#include <cstdarg>
#include "./log_manager.h"

using std::string;
using algorithm::common::Logger;
using algorithm::common::LogManager;
using algorithm::common::LogLevel;

namespace
{
    string buildStringFromVariadicArguments(const char *format_str, va_list vlist)
    {
        char buf[BUFSIZ];
        vsnprintf_s(buf, BUFSIZ, format_str, vlist);
        return string(buf);
    }
}

Logger::Logger(const string &name, LogManager *log_manager):
name_(name),
log_manager_(log_manager)
{

}

void Logger::write(const LogLevel level, const string &what)
{
    log_manager_->write(name_, level, what);
}

void Logger::debug(const string &what)
{
    write(LogLevel::debug, what);
}

void Logger::debug(const char *format_str, ...)
{
    va_list args;
    va_start(args, format_str);
    debug(buildStringFromVariadicArguments(format_str, args));
    va_end(args);
}

void Logger::log(const string &what)
{
    write(LogLevel::debug, what);
}

void Logger::log(const char *format_str, ...)
{
    va_list args;
    va_start(args, format_str);
    log(buildStringFromVariadicArguments(format_str, args));
    va_end(args);
}

void Logger::info(const string &what)
{
    write(LogLevel::info, what);
}

void Logger::info(const char *format_str, ...)
{
    va_list args;
    va_start(args, format_str);
    info(buildStringFromVariadicArguments(format_str, args));
    va_end(args);
}

void Logger::warn(const string &what)
{
    write(LogLevel::warn, what);
}

void Logger::warn(const char *format_str, ...)
{
    va_list args;
    va_start(args, format_str);
    warn(buildStringFromVariadicArguments(format_str, args));
    va_end(args);
}

void Logger::error(const string &what)
{
    write(LogLevel::error, what);
}

void Logger::error(const char *format_str, ...)
{
    va_list args;
    va_start(args, format_str);
    error(buildStringFromVariadicArguments(format_str, args));
    va_end(args);
}
