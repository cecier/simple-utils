/* ************
* Purpose: Simple Logger
* Author:  Mark 'EUL' Fours
************ */

#pragma once

#include <iostream>

namespace simplelogger {

// #TODO
// Main Logic

void Test () {
    std::cout << "test\n";
}



// Simple Logging
// #define LOG_DEBUG(msg)   simplelogger::log(simplelogger::LogLevel::DEBUG, msg, __FILE__, __LINE__)
// #define LOG_INFO(msg)    simplelogger::log(simplelogger::LogLevel::INFO, msg, __FILE__, __LINE__)
// #define LOG_WARNING(msg) simplelogger::log(simplelogger::LogLevel::WARNING, msg, __FILE__, __LINE__)
// #define LOG_ERROR(msg)   simplelogger::log(simplelogger::LogLevel::ERROR, msg, __FILE__, __LINE__)


#define sl simplelogger

} // namespace simplelogger
