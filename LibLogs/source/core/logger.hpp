// Main Logger's File
// Mark Fours


#pragma once
#include <string>

#ifdef LOGGING_EXPORTS
#define LOGGING_API __declspec(dllexport)
#else
#define LOGGING_API __declspec(dllimport)
#endif

extern "C" {

// Уровни логов
enum LogLevel { DEBUG, INFO, WARNING, ERROR };

// Основная функция логирования
LOGGING_API void LogMessage(LogLevel level, const char* message);

// Удобные функции для уровней
LOGGING_API void LogDebug(const char* message);
LOGGING_API void LogInfo(const char* message);
LOGGING_API void LogWarning(const char* message);
LOGGING_API void LogError(const char* message);

}
