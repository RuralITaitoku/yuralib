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
    set_right(1, 1);
    auto [ width, height] = term_.get_term_size();
    while (auto ch = term_.get_char()) {
        if (ch == 'q') {
            break;
        } else if (ch == 'j') {
            if (rrow() < height) {
                row = rrow() + 1;
                col = rcol();
            }
        } else if (ch == 'k') {
            if (rrow() > 1) {
                row = rrow() - 1;
                col = rcol();
            }
        } else if (ch == 'h') {
            if (rcol() > 1) {
                row = rrow();
                col = rcol() - 1;
            }
        } else if (ch == 'l') {
            if (rcol() < width) {
                row = rrow();
                col = rcol() + 1;
            }
        }

        if (ch == 'j' || ch == 'k' || ch == 'h' || ch == 'l') {
            set_right(row, col);
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
    return right_col_;
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

