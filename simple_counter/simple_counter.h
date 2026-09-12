// Simple Counter Header

#pragma once

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

#define ssfile sscount::FileChecker file_checker_

namespace sscount {

class FileChecker {
public:
    explicit FileChecker(const std::string& file_name)
        : file(file_name) {
        init_file();
    }

private:
    void init_file();
    [[nodiscard]] bool is_file_exists() const;

    void calc_file();
    void print_results() const;

    std::string file;

    std::size_t words   = 0;
    std::size_t symbols = 0;
    std::size_t numbers = 0;
    std::size_t spaces  = 0;
};

inline bool FileChecker::is_file_exists() const {
    std::ifstream file_check(file);
    return file_check.is_open();
}

inline void FileChecker::init_file() {
    if (!is_file_exists()) {
        std::cerr
            << "No File Found...\n"
            << "Creating \"" << file << "\"...\n";

        std::ofstream out_file(file);

        if (!out_file.is_open()) {
            std::cerr << "Error: failed to create file \"" << file << "\".\n";
        }

        return;
    }

    std::cout << "Opening the File...\n";
    calc_file();
}

inline void FileChecker::calc_file() {
    std::ifstream ifs(file);

    if (!ifs.is_open()) {
        std::cerr << "Error: failed to open file \"" << file << "\".\n";
        return;
    }

    bool inside_word = false;
    char ch;

    while (ifs.get(ch)) {
        // Spaces / whitespace
        if (std::isspace(static_cast<unsigned char>(ch))) {
            ++spaces;
            inside_word = false;
            continue;
        }

        // Digits
        if (std::isdigit(static_cast<unsigned char>(ch))) {
            ++numbers;
        }

        // Non-whitespace characters
        ++symbols;

        // Word detection
        if (!inside_word) {
            ++words;
            inside_word = true;
        }
    }

    print_results();
}

inline void FileChecker::print_results() const {
    std::cout << "\n"
              << "============================\n"
              << "        File Results\n"
              << "============================\n"
              << "File:    " << file << '\n'
              << "Words:   " << words << '\n'
              << "Symbols: " << symbols << '\n'
              << "Numbers: " << numbers << '\n'
              << "Spaces:  " << spaces << '\n'
              << "============================\n";
}

} // namespace sscount