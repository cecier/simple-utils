/* ************
 * Purpose: ...
 * Author:  Mark 'EUL' Fours
 ************ */


#include <iostream>
#include "simple_counter.h"


int main() {

  sscount::mfile.init_file();

  std::cout << "\nyep";


  // ==== Prevent the console from closing ====
  std::cin.clear();
  std::cin.ignore(32767, '\n');
  std::cin.get();
  // ==========================================
      
}
