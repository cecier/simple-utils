/* ************
 * Purpose: Simple One-Header Symbols (etc..) Counter
 * Author:  Mark 'EUL' Fours
 ************ */

#include <fstream>
#include <iostream>


namespace sscount {

const std::string file_name = "countfile.eul";


class FileChecker {
public:
  void init_file() const;   
  
private:
  bool is_file_exists() const;
}mfile;




inline bool FileChecker::is_file_exists() const {
  std::ifstream file(file_name);
  if (!file) {
    return false;
  }
  return true;
}

inline void FileChecker::init_file() const {
  std::ofstream out_file;

  if (!is_file_exists()) {
    std::cerr << "No File Found... Creating \"countifle.eul\"...\n";
    out_file.open(file_name);
  } else {
    std::cout << "Openning the File...\n";    
  }  
}
  
} // namespace sscount
