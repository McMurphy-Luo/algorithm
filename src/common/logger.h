#ifndef ALGORITHM_COMMON_LOGGER_H
#define ALGORITHM_COMMON_LOGGER_H

#include <string>

namespace algorithm
{
    namespace common
    {
        class LogManager; // forward declearation for LogManager

        enum class LogLevel
        {
            debug,
            log,
            info,
            warn,
            error
        };

        class Logger
        {
            friend class LogManager;
        public:
            void write(const LogLevel level, const std::string &what);

            void debug(const std::string &what);

            void debug(const char *format_str, ...);

            void log(const std::string &what);

            void log(const char *format_str, ...);

            void info(const std::string &what);

            void info(const char *format_str, ...);

            void warn(const std::string &what);

            void warn(const char *format_str, ...);

            void error(const std::string &what);

            void error(const char *format_str, ...);

        protected:
            // Prevent public logger construct, Logger can not be obtained from LogManager::getLogger
            explicit Logger(const std::string &name, LogManager *log_manager);

        private:
            LogManager *log_manager_;
            std::string name_;
        };
    }
}

#endif //ALGORITHM_COMMON_LOGGER_H
