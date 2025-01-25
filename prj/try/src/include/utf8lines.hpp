#include <iostream>

#ifndef __UTF8LINES__
#define __UTF8LINES__


class utf8lines {
public:
    std::vector<char> line;


    void debug_print() {
        std::cout << "debug_print" << std::endl;
    }
    utf8lines& operator=(const std::string& str) {
        for (char ch : str) {
            line.push_back(ch);
        }
        return *this;
    }

    bool operator==(const utf8lines& other) const {
        return line == other.line;
    }
    bool operator==(const std::string& str) const {
        if (str.size() != line.size()) {
            return false;
        }
        for (int i = 0; i < str.size(); ++i) {
            char ch1 = line[i];
            char ch2 = str[i];
            if (ch1 != ch2) {
                return false;
            }
        }
        return true;
    }


    void print(int rows=-1) {
        for (char ch: line) {
            std::cout << ch;
        };
        std::cout << std::endl;
    }

};

#endif


