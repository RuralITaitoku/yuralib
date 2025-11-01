#pragma once

#include <cstdio>
#include <cstdint>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdexcept>
#include <tuple>
#include <iostream>
#include <vector>

class yuraterm {
    struct termios old_termios;
    int width;
    int height;
    std::vector<int64_t> screen;

public:

    yuraterm();
    ~yuraterm();

    unsigned char get_char();
    std::tuple<int, int> get_term_size();

    void to_cursor(int row, int col);
    

    void setup_screen();
    void print();

    static std::string esc_home();
    static std::string esc_clean();
    static std::string esc_end();
    static std::string esc_color(int fg, int bg);
    static std::string esc_fg(int color);
    static std::string esc_bg(int color);
    static std::string esc_cursor(int row, int col);

};

