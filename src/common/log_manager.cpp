#include "log_manager.h"
#include "logger.h"

using namespace algorithm::common;

LogManager* LogManager::instance_ = nullptr;

LogManager::LogManager():
global_filter_(nullptr),
appender_list_(),
buf_("")
{
    
}


void LogManager::enableBuffer(bool enable_or_not)
{
    if (!instance_)
    {
        instance_ = new LogManager();
    }
    
}

Logger LogManager::getLogger(const std::string& logger_name)
{
    return Logger(logger_name, instance_);
}

void LogManager::setGlobalFilter(const Predictor &predictor)
{
    if (!(instance_->global_filter_))
    {
        instance_->global_filter_ = std::make_shared<Predictor>(predictor);
        return;
    }
    
}

void LogManager::registerAppender(const Filter &filter, const Receiver &receiver)
{
    
}
