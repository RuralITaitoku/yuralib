#ifndef __YURA_TERM_HPP__
#define __YURA_TERM_HPP__

#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdexcept>
#include <tuple>

class yuraterm {
    struct termios old_termios, new_termios;

public:
    yuraterm() {
        tcgetattr(STDIN_FILENO, &old_termios); // 現在の設定を取得
        new_termios = old_termios; // 現在の設定をコピー
        
        new_termios.c_lflag &= ~ICANON; // ICANON フラグをオフにする
        new_termios.c_lflag &= ~ECHO; // エコーバックをオフにする (必要であれば)
        new_termios.c_cc[VMIN] = 1; // 1文字ずつ読み取る
        new_termios.c_cc[VTIME] = 0; // タイムアウトなし

        tcsetattr(STDIN_FILENO, TCSANOW, &new_termios); // 変更を適用
    }

    ~yuraterm() {
        tcsetattr(STDIN_FILENO, TCSANOW, &old_termios); // 元の設定に戻す
    }

    unsigned char get_char() {
        return getchar();
    }

    std::tuple<int, int> get_term_size() {
        
        struct winsize size_ioctl;

        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size_ioctl) == -1) {
            throw std::runtime_error("");
        }
        int width = size_ioctl.ws_col;
        int height = size_ioctl.ws_row;
        return std::make_tuple(width, height);
    }
};

#endif
