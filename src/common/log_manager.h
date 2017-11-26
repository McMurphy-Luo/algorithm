#ifndef ALGORITHM_COMMON_LOG_MANAGER_H
#define ALGORITHM_COMMON_LOG_MANAGER_H

#include <memory> // for shared_ptr
#include <functional>
#include <vector>
#include "./logger.h" // for Logger

namespace algorithm
{
    namespace common
    {
        typedef std::function<bool(LogLevel, const std::string&)> Filter;
        typedef std::shared_ptr<std::function<void(const std::string& content)>> Receiver;

        struct Appender
        {
            Filter filter;
            Receiver receiver;
        };

        class LogManager
        {
        public:
            static Logger getLogger(const std::string &logger_name);

            static void setGlobalFilter(const Filter &filter);

            static void registerAppender(const Filter &filter, const Receiver &receiver);

            static void unRegisterAppender(const Receiver &receiver);

            static void enableBuffer(bool enable_or_not);

            static void enableEnsureLineEnding(bool enable_or_not);

            // Loggers use next method to write their record to appender.
            void write(const std::string &from, LogLevel level, const std::string &content);

            // This should only be called for debug reasons. Beacause the instance_ is created
            // first call to LogManager and never be freed. "instance_" is considered memory leak.
            // When using some tool to detect memory leaks, users could use next function to free
            // the global singleton instance_ so that prevent memory leaks in this module.
            // In normal release build, never call it. "instance_" is an safe memory leak, it will
            // be recycled when the program shuts down.
            static void freeLogManager() { delete instance_; };

        private:
            static LogManager* instance_;

        protected:
            // Prevent public instance construct. This is a singleton class.
            LogManager();
            LogManager(const LogManager& another) = delete; // forbid copy
            LogManager& operator=(const LogManager& another) = delete; // forbid copy

        private:
            Filter global_filter_;
            std::vector<Appender> appender_list_;
            bool buf_enabled_;
            std::string buf_;
            bool ensure_line_ending_;
        };
    }
}

#endif //ALGORITHM_COMMON_LOG_MANAGER_H
