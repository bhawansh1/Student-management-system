#include "Logger.hpp"

namespace Core {

    Logger& Logger::getInstance() {
        static Logger instance;
        return instance;
    }

    Logger::Logger() : fileLoggingEnabled(false) {}

    Logger::~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    void Logger::setLogFile(const std::string& filename) {
        std::lock_guard<std::mutex> lock(logMutex);
        if (logFile.is_open()) {
            logFile.close();
        }
        logFile.open(filename, std::ios::app);
        fileLoggingEnabled = logFile.is_open();
    }

    void Logger::log(LogLevel level, const std::string& message) {
        std::lock_guard<std::mutex> lock(logMutex);
        
        std::string timestamp = getTimestamp();
        std::string levelStr = levelToString(level);
        std::string formattedMessage = "[" + timestamp + "] [" + levelStr + "] " + message;

        // Console output
        // Use colors for console
        std::string colorCode = "";
        switch(level) {
            case LogLevel::INFO: colorCode = "\033[32m"; break; // Green
            case LogLevel::WARNING: colorCode = "\033[33m"; break; // Yellow
            case LogLevel::ERROR: colorCode = "\033[31m"; break; // Red
            case LogLevel::DEBUG: colorCode = "\033[36m"; break; // Cyan
        }
        std::cout << colorCode << formattedMessage << "\033[0m" << std::endl;

        // File output
        if (fileLoggingEnabled) {
            logFile << formattedMessage << std::endl;
        }
    }

    std::string Logger::getTimestamp() {
        auto now = std::chrono::system_clock::now();
        auto timeT = std::chrono::system_clock::to_time_t(now);
        std::tm tmStruct;
        localtime_r(&timeT, &tmStruct);
        
        std::stringstream ss;
        ss << std::put_time(&tmStruct, "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }

    std::string Logger::levelToString(LogLevel level) {
        switch (level) {
            case LogLevel::INFO: return "INFO";
            case LogLevel::WARNING: return "WARNING";
            case LogLevel::ERROR: return "ERROR";
            case LogLevel::DEBUG: return "DEBUG";
            default: return "UNKNOWN";
        }
    }

}
