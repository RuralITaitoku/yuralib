#include <cstdio>
#include <termios.h>
#include <unistd.h>


#ifndef __YURA_TERM_HPP__
#define __YURA_TERM_HPP__

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
};

#endif
