/* ********** */
/* Purpose: Test file for the headers
/* Author:  Mark 'EUL' Fours
/************ */


#include <iostream>
#include "simplevector.hpp"


int main(void) {


    ss::Vector <int> name;
    name.Set(0, 12);

    std::cout << name.Get(0) << std::endl;

    // test

    // ==== Prevent the console from closing ====
    std::cin.clear();
    
    std::cin.ignore(32767, '\n');
    std::cin.get();
    // ================
    
    
    
    return 0;
}