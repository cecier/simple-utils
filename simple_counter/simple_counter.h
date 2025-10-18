/* ************
 * Purpose: Simple One-Header Symbols (etc..) Counter
 * Author:  Mark 'EUL' Fours
 ************ */

#include <fstream>
#include <iostream>

#define ssb sscount::FileChecker file_checker


namespace sscount {

// const std::string file_name = "countfile.eul";



class FileChecker {
public:
  // void set_file
  FileChecker(std::string file_name) : file(file_name + ".eul") {
    init_file();    
  }
private:
  void init_file() const;
  bool is_file_exists(std::string file) const;
  std::string file;    
};


  inline bool FileChecker::is_file_exists(std::string file) const {
  std::ifstream file_check(file);
  if (!file_check) {
    return false;
  }
  return true;
}

inline void FileChecker::init_file() const {
  std::ofstream out_file;

  if (!is_file_exists(file)) {
    std::cerr << "No File Found... \nCreating \"" << file << "\"...\n";
    out_file.open(file);
  } else {
    std::cout << "Openning the File...\n";    
  }
}
  
} // namespace sscount
