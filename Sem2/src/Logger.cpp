#include "Logger.h"
namespace lg {
    std::ofstream Logger::fileStream;
    bool Logger::consoleOutputEnabled = true;
    bool Logger::fileOutputEnabled = true;
    bool Logger::includeTimestamps = false;

    void Logger::Initialize(const std::string &logFilePath) {
        fileStream.open(logFilePath, std::ios::out | std::ios::app);
    }

    void Logger::EnableConsoleOutput(bool enable) {
        consoleOutputEnabled = enable;
    }

    void Logger::EnableFileOutput(bool enable) {
        fileOutputEnabled = enable;
    }

    void Logger::EnableTimestamps(bool enable) {
        includeTimestamps = enable;
    }

    void Logger::Log(LogLevel level, const std::string &message) {
        std::string logLevelString = GetLogLevelString(level);
        std::string currentTime;

        if (includeTimestamps)
            currentTime = GetCurrentTime();

        std::string logEntry = "[" + currentTime + "] " + logLevelString + ": " + message;

        if (consoleOutputEnabled)
            std::cout << logEntry << std::endl;

        if (fileOutputEnabled && fileStream.is_open())
            fileStream << logEntry << std::endl;
    }

    std::string Logger::GetLogLevelString(LogLevel level) {
        switch (level) {
            case LogLevel::Debug:
                return "DEBUG";
            case LogLevel::Info:
                return "INFO";
            case LogLevel::Error:
                return "ERROR";
            default:
                return "UNKNOWN";
        }
    }

    std::string Logger::GetCurrentTime() {
        std::time_t currentTime = std::time(nullptr);
        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&currentTime));
        return buffer;
    }
}