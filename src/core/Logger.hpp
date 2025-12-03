#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace Core {

    enum class LogLevel {
        INFO,
        WARNING,
        ERROR,
        DEBUG
    };

    class Logger {
    public:
        // Delete copy constructor and assignment operator for Singleton
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        static Logger& getInstance();

        void log(LogLevel level, const std::string& message);
        void setLogFile(const std::string& filename);

    private:
        Logger();
        ~Logger();

        std::string getTimestamp();
        std::string levelToString(LogLevel level);

        std::mutex logMutex;
        std::ofstream logFile;
        bool fileLoggingEnabled;
    };

}
