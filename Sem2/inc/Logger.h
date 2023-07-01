#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
namespace lg {
    enum class LogLevel {
        Debug,
        Info,
        Error
    };

    class Logger {
    public:
        static void Initialize(const std::string &logFilePath);

        static void EnableConsoleOutput(bool enable);

        static void EnableFileOutput(bool enable);

        static void EnableTimestamps(bool enable);

        static void Log(LogLevel level, const std::string &message);

    private:
        static std::ofstream fileStream;
        static bool consoleOutputEnabled;
        static bool fileOutputEnabled;
        static bool includeTimestamps;

        static std::string GetLogLevelString(LogLevel level);

        static std::string GetCurrentTime();
    };
}