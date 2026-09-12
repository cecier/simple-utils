// Test File for the Simple Counter Header


#include <iostream>
#include <string>
#include "simple_counter.h"


int main(int argc, char** argv) {

  if (argc > 1) {
    std::cout << "Curernt File Name is: "; 
    ssfile(argv[1]);
    return 0;
  }

  std::cout << "Enter File Name -> : ";  
  std::string file_name{};
  std::cin >> file_name;  
  ssfile(file_name);

  return 0;
}