#include "log_manager.h"
#include <algorithm>
#include "logger.h"

using namespace algorithm::common;

LogManager* LogManager::instance_ = nullptr;

Logger LogManager::getLogger(const std::string &logger_name)
{
    if (!instance_)
    {
        instance_ = new LogManager();
    }
    return Logger(logger_name, instance_);
}

void LogManager::setGlobalFilter(const Filter &filter)
{
    if (!instance_)
    {
        instance_ = new LogManager();
    }
    instance_->global_filter_ = filter;
}

void LogManager::registerAppender(const Filter &filter, const Receiver &receiver)
{
    if (!instance_)
    {
        instance_ = new LogManager();
    }
    Appender new_appender;
    new_appender.filter = filter;
    new_appender.receiver = receiver;
    instance_->appender_list_.push_back(new_appender);
}

void LogManager::unRegisterAppender(const Receiver &receiver)
{
    if (!instance_)
    {
        return;
    }
    instance_->appender_list_.erase(std::remove_if(instance_->appender_list_.begin(), instance_->appender_list_.end(), [&](const Appender &appender) { return appender.receiver == receiver; }), instance_->appender_list_.end());
}

void LogManager::enableBuffer(bool enable_or_not)
{
    if (!instance_)
    {
        instance_ = new LogManager();
    }
    instance_->buf_enabled_ = enable_or_not;
}

LogManager::LogManager():
global_filter_(),
appender_list_(),
buf_enabled_(false),
buf_(),
ensure_line_ending_(false)
{
    
}

void LogManager::write(const std::string &from, LogLevel level, const std::string &content)
{
    if (!instance_)
    {
        instance_ = new LogManager();
    }
    if (global_filter_)
    {
        if (!global_filter_(level, from))
        {
            return;
        }
    }
    for (const Appender &appender : instance_->appender_list_)
    {
        if (appender.filter(level, from))
        {
            appender.receiver->operator()(content);
        }
    }
}
