#include "yuraterm.hpp"


yuraterm::yuraterm() {
    struct termios  new_termios;

    tcgetattr(STDIN_FILENO, &old_termios); // 現在の設定を取得
    new_termios = old_termios; // 現在の設定をコピー
    
    new_termios.c_lflag &= ~ICANON; // ICANON フラグをオフにする
    new_termios.c_lflag &= ~ECHO; // エコーバックをオフにする (必要であれば)
    new_termios.c_cc[VMIN] = 1; // 1文字ずつ読み取る
    new_termios.c_cc[VTIME] = 0; // タイムアウトなし

    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios); // 変更を適用
}

yuraterm::~yuraterm() {
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios); // 元の設定に戻す 
}

unsigned char yuraterm::get_char() {
    return getchar();
}


std::tuple<int, int> yuraterm::get_term_size() {
    struct winsize size_ioctl;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size_ioctl) == -1) {
        throw std::runtime_error("");
    }
    int width = size_ioctl.ws_col;
    int height = size_ioctl.ws_row;
    return std::make_tuple(width, height);
}

std::string yuraterm::esc_home() {
    return "\e[H";
}
std::string yuraterm::esc_clean() {
    return "\e[2J";
}
std::string yuraterm::esc_end() {
    return "\e[0m";
}
std::string yuraterm::esc_fg(int color) {
    std::string result = "\e[3";
    result += std::to_string(color);
    result += "m";
    return result;
}
std::string yuraterm::esc_bg(int color) {
    std::string result = "\e[4";
    result += std::to_string(color);
    result += "m";
    return result;
}
std::string yuraterm::esc_cursor(int row, int col){
    std::string result = "\e[";
    result += row;
    result += ";";
    result += col;
    result += "H";
    return result;
}

 
