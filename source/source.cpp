/* ********** */
/* Purpose: Test file for the headers
/* Author:  Mark 'EUL' Fours
/************ */




#include <iostream>
#include <string>
#include "simplelogger.hpp"

int main() {

    // sl::Test();

    LOG_ERROR("test");
    LOG_WARNING("test");
    LOG_INFO("test");
    LOG_ERROR("test");
    LOG_DEBUG("test");
    LOG_WARNING("test");

    // printf("%c[%dmHELLO!\n", 0x1B, 32);


    std::cin.clear();
    std::cin.ignore(32767, '\n');
    std::cin.get();
    return 0;
}
