#pragma once

#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdexcept>
#include <tuple>
#include <iostream>

class yuraterm {
    struct termios old_termios;

public:

    yuraterm();
    ~yuraterm();

    unsigned char get_char();
    std::tuple<int, int> get_term_size();
    static std::string esc_home();
    std::string esc_clean();
    std::string esc_end();
    std::string esc_fg(int color);
    std::string esc_bg(int color);
    std::string esc_cursor(int row, int col);
};

