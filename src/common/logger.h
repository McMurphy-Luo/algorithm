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

            void log(const std::string &what);

            void info(const std::string &what);

            void warn(const std::string &what);

            void error(const std::string &what);

        protected:
            explicit Logger(const std::string &name, LogManager *log_manager);

        private:
            LogManager *log_manager_;
            std::string name_;
        };
    }
}

#endif //ALGORITHM_COMMON_LOGGER_H
