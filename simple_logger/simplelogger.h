// Simple Logger Header

#pragma once

#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>

#ifdef _WIN32
    #include <windows.h>
#endif


namespace simplelogger {


// ============================================================
// Configuration
// ============================================================

inline constexpr const char* DEFAULT_LOG_FILE = "simpleutils.log";


// ============================================================
// Thread Safety
// ============================================================

inline std::mutex& GetMutex() {
    static std::mutex mutex;
    return mutex;
}


// ============================================================
// Log Types
// ============================================================

enum class LogType {
    SIMPLE_LOG_DEBUG,
    SIMPLE_LOG_INFO,
    SIMPLE_LOG_WARNING,
    SIMPLE_LOG_ERROR
};


// ============================================================
// Log Type → String
// ============================================================

inline const char* GetLogTypeName(LogType type) {
    switch (type) {
        case LogType::SIMPLE_LOG_DEBUG:
            return "DEBUG";

        case LogType::SIMPLE_LOG_INFO:
            return "INFO";

        case LogType::SIMPLE_LOG_WARNING:
            return "WARNING";

        case LogType::SIMPLE_LOG_ERROR:
            return "ERROR";

        default:
            return "UNKNOWN";
    }
}


// ============================================================
// Current Local Time
// ============================================================

inline std::string GetCurrentUserTime() {
    const auto now = std::chrono::system_clock::now();
    const std::time_t now_c =
        std::chrono::system_clock::to_time_t(now);

    std::tm local_tm{};

#ifdef _WIN32
    localtime_s(&local_tm, &now_c);
#else
    localtime_r(&now_c, &local_tm);
#endif

    char buffer[32]{};

    std::strftime(
        buffer,
        sizeof(buffer),
        "%Y-%m-%d %H:%M:%S",
        &local_tm
    );

    return std::string(buffer);
}


// ============================================================
// Windows Console Colors
// ============================================================

#ifdef _WIN32

inline WORD GetConsoleColor(LogType type) {
    switch (type) {
        case LogType::SIMPLE_LOG_DEBUG:
            return FOREGROUND_BLUE | FOREGROUND_INTENSITY;

        case LogType::SIMPLE_LOG_INFO:
            return FOREGROUND_GREEN | FOREGROUND_INTENSITY;

        case LogType::SIMPLE_LOG_WARNING:
            return FOREGROUND_RED |
                   FOREGROUND_GREEN |
                   FOREGROUND_INTENSITY;

        case LogType::SIMPLE_LOG_ERROR:
            return FOREGROUND_RED | FOREGROUND_INTENSITY;

        default:
            return FOREGROUND_RED |
                   FOREGROUND_GREEN |
                   FOREGROUND_BLUE;
    }
}

#endif


// ============================================================
// Console Logging
// ============================================================

inline void LogConsoleMessage(
    LogType type,
    const std::string& message
) {
    std::lock_guard<std::mutex> lock(GetMutex());

    const std::string output =
        "(" + GetCurrentUserTime() + ") [" +
        GetLogTypeName(type) + "] " +
        message;

#ifdef _WIN32

    HANDLE console =
        GetStdHandle(STD_OUTPUT_HANDLE);

    if (console == INVALID_HANDLE_VALUE ||
        console == nullptr) {
        std::cout << output << '\n';
        return;
    }

    CONSOLE_SCREEN_BUFFER_INFO console_info{};

    if (!GetConsoleScreenBufferInfo(
            console,
            &console_info)) {
        std::cout << output << '\n';
        return;
    }

    const WORD saved_color =
        console_info.wAttributes;

    SetConsoleTextAttribute(
        console,
        GetConsoleColor(type)
    );

    std::cout << output << '\n';

    // Restore original color.
    SetConsoleTextAttribute(
        console,
        saved_color
    );

#else

    std::cout << output << '\n';

#endif
}


// ============================================================
// File Logging
// ============================================================

inline void LogFileMessage(
    LogType type,
    const std::string& message,
    const std::string& filename = DEFAULT_LOG_FILE
) {
    std::lock_guard<std::mutex> lock(GetMutex());

    std::ofstream logfile(
        filename,
        std::ios::app
    );

    if (!logfile.is_open()) {
        return;
    }

    logfile
        << "(" << GetCurrentUserTime() << ") "
        << "[" << GetLogTypeName(type) << "] "
        << message
        << '\n';
}


// ============================================================
// Combined Logging
// ============================================================

inline void LogMessage(
    LogType type,
    const std::string& message
) {
    LogConsoleMessage(type, message);
    LogFileMessage(type, message);
}


// ============================================================
// Logger
// ============================================================

class Logger {
public:

    explicit Logger(LogType type)
        : type_(type) {
    }

    ~Logger() {
        if (!buffer_.str().empty()) {
            LogMessage(type_, buffer_.str());
        }
    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    Logger(Logger&& other) noexcept
        : type_(other.type_),
          buffer_(std::move(other.buffer_)),
          active_(other.active_) {
        other.active_ = false;
    }

    Logger& operator=(Logger&& other) noexcept {
        if (this != &other) {
            type_ = other.type_;
            buffer_ = std::move(other.buffer_);
            active_ = other.active_;

            other.active_ = false;
        }

        return *this;
    }

    template <typename T>
    Logger& operator<<(const T& value) {
        buffer_ << value;
        return *this;
    }

    Logger& operator<<(
        std::ostream& (*manipulator)(std::ostream&)
    ) {
        manipulator(buffer_);
        return *this;
    }

private:
    LogType type_;
    std::ostringstream buffer_;
    bool active_ = true;
};


// ============================================================
// Simple Functions
// ============================================================

inline void GetLogDebug(const char* message) {
    LogMessage(
        LogType::SIMPLE_LOG_DEBUG,
        message
    );
}

inline void GetLogInfo(const char* message) {
    LogMessage(
        LogType::SIMPLE_LOG_INFO,
        message
    );
}

inline void GetLogWarning(const char* message) {
    LogMessage(
        LogType::SIMPLE_LOG_WARNING,
        message
    );
}

inline void GetLogError(const char* message) {
    LogMessage(
        LogType::SIMPLE_LOG_ERROR,
        message
    );
}


// ============================================================
// Macros
// ============================================================

#define LOG_DEBUG \
    simplelogger::Logger( \
        simplelogger::LogType::SIMPLE_LOG_DEBUG \
    )

#define LOG_INFO \
    simplelogger::Logger( \
        simplelogger::LogType::SIMPLE_LOG_INFO \
    )

#define LOG_WARNING \
    simplelogger::Logger( \
        simplelogger::LogType::SIMPLE_LOG_WARNING \
    )

#define LOG_ERROR \
    simplelogger::Logger( \
        simplelogger::LogType::SIMPLE_LOG_ERROR \
    )


#define simplog simplelogger

} // namespace simplelogger