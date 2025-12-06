#include "yuraterm.hpp"

yuraterm::yuraterm() {
    std::cout << "\e[?1049h";
    struct termios  new_termios;

    tcgetattr(STDIN_FILENO, &old_termios); // 現在の設定を取得
    new_termios = old_termios; // 現在の設定をコピー
    
    new_termios.c_lflag &= ~ICANON; // ICANON フラグをオフにする
    new_termios.c_lflag &= ~ECHO; // エコーバックをオフにする (必要であれば)
    new_termios.c_cc[VMIN] = 1; // 1文字ずつ読み取る
    new_termios.c_cc[VTIME] = 0; // タイムアウトなし

    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios); // 変更を適用
    get_term_size();
}

yuraterm::~yuraterm() {

    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios); // 元の設定に戻す 
    std::cout << "\e[?1049l";
}

unsigned char yuraterm::get_char() {
    return getchar();
}

std::string yuraterm::getline() {
    std::string line;

    for (;;) {
        auto ch = get_char();
        if (ch == '\n') {
            line += "[ret]";
            return line;
        } else if (ch == '\t') {
            line += "[tab]";
        } else if (ch == '\b') {
            line += "[bs]";
        } else if (ch < ' ') {
            line += "[" + std::to_string(static_cast<int>(ch)) + "]";
        } else {
            line += ch;
        }
        std::cout << std::to_string(static_cast<int>(ch)) << std::endl;
        std::cout << line << std::endl;
    }
}

std::tuple<int, int> yuraterm::get_term_size() {
    struct winsize size_ioctl;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size_ioctl) == -1) {
        throw std::runtime_error("");
    }
    width = size_ioctl.ws_col;
    height = size_ioctl.ws_row;
    return std::make_tuple(width, height);
}

std::string yuraterm::home() {
    return "\e[H";
}
std::string yuraterm::clean() {
    return "\e[2J";
}
std::string yuraterm::end() {
    return "\e[0m";
}
std::string yuraterm::color(int fg, int bg) {
    std::string result = "\e[3";
    result += std::to_string(fg);
    result += "m";
    result += "\e[4";
    result += std::to_string(bg);
    result += "m";
    return result;
}
std::string yuraterm::fg(int color) {
    std::string result = "\e[3";
    result += std::to_string(color);
    result += "m";
    return result;
}
std::string yuraterm::bg(int color) {
    std::string result = "\e[4";
    result += std::to_string(color);
    result += "m";
    return result;
}
std::string yuraterm::cursor(int row, int col){
    std::string result = "\e[";
    result += std::to_string(row);
    result += ";";
    result += std::to_string(col);
    result += "H";
    return result;
}

void yuraterm::to_cursor(int row, int col) {

    printf("\e[%d;%dH", row, col);
}


void yuraterm::setup_screen() {
    screen.resize(width * height, static_cast<uint64_t>(' '));
}