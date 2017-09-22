#include "logger.h"
#include "log_manager.h"

using namespace algorithm::common;

Logger::Logger(const std::string& name, LogManager* log_manager):
name_(name),
log_manager_(log_manager)
{

}

void Logger::write(const LogLevel level, const std::string& what)
{
    log_manager_->write(name_, level, what);
}

void Logger::debug(const std::string& what)
{
    write(LogLevel::debug, what);
}

void Logger::log(const std::string& what)
{
    write(LogLevel::debug, what);
}

void Logger::info(const std::string& what)
{
    write(LogLevel::info, what);
}

void Logger::warn(const std::string& what)
{
    write(LogLevel::warn, what);
}

void Logger::error(const std::string& what)
{
    write(LogLevel::error, what);
}
