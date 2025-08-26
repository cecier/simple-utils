// Main Logger's File
// Mark Fours


#include "logger.hpp"
#include <iostream>
#include <mutex>
#include <chrono>
#include <iomanip>

std::mutex log_mutex;

const char* LevelToString(LogLevel level) {
    switch(level) {
        case DEBUG: return "DEBUG";
        case INFO: return "INFO";
        case WARNING: return "WARNING";
        case ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

void LogMessage(LogLevel level, const char* message) {
    std::lock_guard<std::mutex> lock(log_mutex);

    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);

    std::cout << "[" << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S") << "] ";
    std::cout << "[" << LevelToString(level) << "] ";
    std::cout << message << std::endl;
}

void LogDebug(const char* message)   { LogMessage(DEBUG, message); }
void LogInfo(const char* message)    { LogMessage(INFO, message); }
void LogWarning(const char* message) { LogMessage(WARNING, message); }
void LogError(const char* message)   { LogMessage(ERROR, message); }
