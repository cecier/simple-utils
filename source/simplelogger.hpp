/* ************
* Purpose: Simple Logger
* Author:  Mark 'EUL' Fours
************ */

#pragma once

#include <iostream>
#include <mutex>
#include <windows.h>
#include <chrono>
#include <ctime>
#include <string>


// #TODO
// * Add File Logging
//  ** Read / Write / etc.
// =====

namespace simplelogger {


inline std::mutex& GetMutex() {
    static std::mutex mtx;
    return mtx;
}


// Types of Logs
enum class LogType {
    SIMPLE_LOG_DEBUG,
    SIMPLE_LOG_INFO,
    SIMPLE_LOG_WARNING,
    SIMPLE_LOG_ERROR
};


// Colored Console (Windows)
inline WORD GetConsoleColor(LogType type) {
    switch(type) {
        case LogType::SIMPLE_LOG_DEBUG:   return FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        case LogType::SIMPLE_LOG_INFO:    return FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        case LogType::SIMPLE_LOG_WARNING: return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
        case LogType::SIMPLE_LOG_ERROR:   return FOREGROUND_RED | FOREGROUND_INTENSITY;
        default: return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    }
}


inline std::string GetCurrentUserTime(){
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    std::tm local_tm{};

#ifdef _WIN32
    localtime_s(&local_tm, &now_c); // Safe for the Windows
#else
    localtime_r(&now_c, &local_tm); // Safe for the Linux
#endif

    char buffer[16];
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S", &local_tm);
    return std::string(buffer);
}


// Print with Colored Text
inline void LogConsoleMessage(LogType type, const char* msg) {
    std::lock_guard<std::mutex> lock(GetMutex());

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    // Saving the curr color
    WORD savedColor = csbi.wAttributes;

    // Set a new color
    SetConsoleTextAttribute(hConsole, GetConsoleColor(type));

    const char* prefix = "";
    switch(type) {
        case LogType::SIMPLE_LOG_DEBUG:   prefix = "[DEBUG]"; break;
        case LogType::SIMPLE_LOG_INFO:    prefix = "[INFO]"; break;
        case LogType::SIMPLE_LOG_WARNING: prefix = "[WARNING]"; break;
        case LogType::SIMPLE_LOG_ERROR:   prefix = "[ERROR]"; break;
    }

    std::cout << "(" << GetCurrentUserTime() << ") " << prefix << " " << msg << "\n";

    // Set back the origin color
    SetConsoleTextAttribute(hConsole, savedColor);
}




#define simplog simplelogger

inline void GetLogDebug(const char* msg)   { LogConsoleMessage(LogType::SIMPLE_LOG_DEBUG, msg); }
inline void GetLogInfo(const char* msg)    { LogConsoleMessage(LogType::SIMPLE_LOG_INFO, msg); }
inline void GetLogWarning(const char* msg) { LogConsoleMessage(LogType::SIMPLE_LOG_WARNING, msg); }
inline void GetLogError(const char* msg)   { LogConsoleMessage(LogType::SIMPLE_LOG_ERROR, msg); }

#define LOG_DEBUG(msg)   simplelogger::GetLogDebug(msg)
#define LOG_INFO(msg)    simplelogger::GetLogInfo(msg)
#define LOG_WARNING(msg) simplelogger::GetLogWarning(msg)
#define LOG_ERROR(msg)   simplelogger::GetLogError(msg)


} // namespace simplelogger
