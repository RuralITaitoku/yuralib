#include "ivvi.hpp"
#include "yura.hpp"
#include "task.hpp"
#include <iostream>

#include <fstream>

std::ofstream debug_log("log.txt");

ivvi::ivvi() {
    std::cout << "ivvi constructor" << std::endl;
}

ivvi::~ivvi() {
    std::cout << "ivvi distructor" << std::endl;
}

std::string ivvi::help() {
    std::string result = "iv";
    return result;
}
bool ivvi::run(std::string &cmd, std::vector<std::string>& stack) {
    yuraterm term;
    int row = 1;
    int col = 1;
    auto [ width, height] = term.get_term_size();
    debug_log << "-width=" << width << " height=" << height << std::endl;
    while (auto ch = term.get_char()) {
        if (ch == 'q') {
            break;
        } else if (ch == 'j') {
            if (row < height) {
                row++;
            }
            term.to_cursor(row, col);
        } else if (ch == 'k') {
            if (row > 1) {
                row--;
            }
            term.to_cursor(row, col);
        } else if (ch == 'h') {
            if (col > 1) {
                col--;
            }
            term.to_cursor(row, col);
        } else if (ch == 'l') {
            if (col < width) {
                col++;
            }
            term.to_cursor(row, col);
        }
    }
    return true;
}

