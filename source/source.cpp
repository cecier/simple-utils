/* ************
* Purpose: Test file for the headers
* Author:  Mark 'EUL' Fours
************ */


#include <iostream>
#include <string>
#include "simplelogger.hpp"

int main() {

    sl::Test();

    std::cin.clear();
    std::cin.ignore(32767, '\n');
    std::cin.get();
    return 0;
}
