#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#define ssfile sscount::FileChecker file_checker_

namespace sscount {

class FileChecker {
public:
  FileChecker(const std::string& file_name) : file(file_name + ".eul") {
      init_file();
  }

private:
  void init_file();
  bool is_file_exists() const;

  void calc_file();
  void print_results() const;

  std::string file;
  std::vector<std::string> words;
};


inline bool FileChecker::is_file_exists() const {
  std::ifstream file_check(file);
  return file_check.good();
}

inline void FileChecker::init_file() {
  if (!is_file_exists()) {
    std::cerr << "No File Found... \nCreating \"" << file << "\"...\n";
    std::ofstream out_file(file); // RAII: file auto-closed
  } else {
    std::cout << "Opening the File...\n";
    calc_file();
  }
}

inline void FileChecker::calc_file() {
  std::ifstream ifs(file);
  std::string temp;
  while (ifs >> temp) {
    words.push_back(temp);
  }
  print_results();
}

inline void FileChecker::print_results() const {
  std::cout << "\n\nTotal amount of words: " << words.size() << "\n";
  // @TODO : Total amount of symbols
  // @TODO : Total amount of numbers
  // @TODO : Total amount of spaces  
}

} // namespace sscount
