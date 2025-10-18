/* ************
 * Purpose: Test File for the Simple Counter Header Lib
 * Author:  Mark 'EUL' Fours
 ************ */


#include <iostream>
#include "simple_counter.h"


int main() {
  std::cout << "File Name -> : ";  
  std::string file_name{};
  std::cin >> file_name;  
  ssfile(file_name);
  // ssb.init_file();

  // std::cout << "\nchecktest";


  // ==== Prevent the console from closing ====
  std::cin.clear();
  std::cin.ignore(32767, '\n');
  std::cin.get();
  // ==========================================
      
}
