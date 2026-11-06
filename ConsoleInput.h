#pragma once
#include <istream>
#include <ostream>
#include <sstream>
#include <string>

inline bool readSquare(std::istream& input, std::ostream& output,
                       const char* prompt, int size, int& column, int& row) {
    std::string line;
    while (output << prompt, std::getline(input >> std::ws, line)) {
        std::istringstream parser(line);
        char letter, extra;
        int number;
        if ((parser >> letter >> number) && !(parser >> extra) &&
            letter >= 'A' && letter < 'A' + size && number >= 1 && number <= size) {
            column = letter - 'A';
            row = number - 1;
            return true;
        }
        output << "Invalid square. Use an uppercase column and a valid row.\n";
    }
    return false;
}

inline bool readChoice(std::istream& input, std::ostream& output,
                       const char* prompt, int maximum, int& choice) {
    std::string line;
    while (output << prompt, std::getline(input >> std::ws, line)) {
        std::istringstream parser(line);
        int number;
        char extra;
        if ((parser >> number) && !(parser >> extra) && number >= 1 && number <= maximum) {
            choice = number - 1;
            return true;
        }
        output << "Invalid choice. Select a displayed card number.\n";
    }
    return false;
}
