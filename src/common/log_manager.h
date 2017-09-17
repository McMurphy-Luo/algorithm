#ifndef ALGORITHM_COMMON_LOG_MANAGER_H
#define ALGORITHM_COMMON_LOG_MANAGER_H

#include <memory> // for shared_ptr
#include <functional>
#include <vector>
#include "logger.h" // for Logger

namespace algorithm
{
    namespace common
    {
        typedef std::function<bool(LogLevel, const std::string&)> Predictor;
        typedef std::shared_ptr<Predictor> Filter;
        typedef std::shared_ptr<std::function<void(const char* buf, std::size_t buf_size)>> Receiver;

        struct Appender
        {
            Filter filter;
            Receiver receiver;
        };

        class LogManager
        {
        public:
            static Logger getLogger(const std::string &logger_name);

            static void setGlobalFilter(const Predictor &predictor);

            static void registerAppender(const Filter &filter, const Receiver &receiver);

            static void enableBuffer(bool enable_or_not);

        private:
            static LogManager* instance_;

        protected:
            LogManager();

        private:
            std::shared_ptr<Predictor> global_filter_;
            std::vector<Appender> appender_list_;
            bool buf_enabled_;
            std::string buf_;
        };
    }
}

#endif //ALGORITHM_COMMON_LOG_MANAGER_H
