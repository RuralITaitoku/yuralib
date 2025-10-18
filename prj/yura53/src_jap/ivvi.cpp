#include "ivvi.hpp"
#include "task.hpp"
#include <iostream>

#include <fstream>


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
    int row = 1;
    int col = 1;
    auto [ width, height] = term_.get_term_size();
    while (auto ch = term_.get_char()) {
        if (ch == 'q') {
            break;
        } else if (ch == 'j') {
            if (row < height) {
                row++;
            }
            term_.to_cursor(row, col);
        } else if (ch == 'k') {
            if (row > 1) {
                row--;
            }
            term_.to_cursor(row, col);
        } else if (ch == 'h') {
            if (col > 1) {
                col--;
            }
            term_.to_cursor(row, col);
        } else if (ch == 'l') {
            if (col < width) {
                col++;
            }
            term_.to_cursor(row, col);
        }
    }
    return true;
}

int ivvi::height() {
    return height_;
}
int ivvi::width() {
    return width_;
}

int ivvi::center_col() {
    return center_col_;
}

int ivvi::lrow() {
    return left_row_;
}
int ivvi::lcol() {
    return left_col_;
}

int ivvi::rrow() {
    return right_row_;
}
int ivvi::rcol() {
    return right_row_;
}

void ivvi::set_left(int r, int c) {
    row_ = r;
    col_ = c;
    left_row_ = r;
    left_col_ = c;
}

void ivvi::set_right(int r, int c) {
    row_ = r;
    col_ = c;
    right_row_ = r;
    right_col_ = c;
}

int ivvi::print(const std::string& str, int fg, int bg) {
    return 0;
}

