/* ********** */
/* Purpose: Test file for the headers
/* Author:  Mark 'EUL' Fours
/************ */


#include <iostream>
#include "simplevector.hpp"
#include <vector>


int main(void) {


    ss::Vector <int> name;
    name.Set(0, 12);
    name.Set(100, 8);

    // std::cout << name.Get(0) << name.Get(100) << std::endl;
    std::cout << name[100] << std::endl;




    // test

    // ==== Prevent the console from closing ====
    std::cin.clear();
    
    std::cin.ignore(32767, '\n');
    std::cin.get();
    // ================
    
    
    
    return 0;
}