#include "jap0.hpp"

bool jap0::check_line(const std::string& text, std::string& prefix, int& no, std::string& line) {
    std::string src;
    if (text.empty()) {
        return false;
    }
    if (text[0] == 'a') {
        prefix = "a";
        src = text.substr(1);
    } else if (text[0] == 'i') {
        prefix = "i";
        src = text.substr(1);
    } else if (text[0] == 'c') {
        prefix = "c";
        src = text.substr(1);
    } else {
        src = text;
    }
    std::smatch matches;
    if (std::regex_search(src, matches, line_pattern_)) {
        auto str_no = matches[1].str();
        if (!str_no.empty()) {
            no = std::stoi(str_no);
        } else {
            no = INT_MAX;
        }
        line = matches[2].str();
        return true;
    } else {
        return false;
    }
}

bool jap0::check_pattern(const std::string& text, const std::regex& pattern, std::vector<std::string>& result) {
    return false;
}

void jap0::help() {
    std::cout << "jap0" << std::endl;
}
bool jap0::run(const std::string& cmd, std::vector<std::string>& stack) {
    int row_no;
    std::string row_cmd;
    std::string row_line;
    if(check_line(cmd, row_cmd, row_no, row_line)) {
        std::cout << row_cmd << " " << row_no << ". " << row_line << std::endl;
        return true;
    } else if (cmd == "jap0") {
        std::cout << "jap0 test" << std::endl;
        return true;
    }
    return false;
}


void jap0_screen::init(int width, int height) {
    height_ = height;
    width_ = width;
    screen_.resize(height * width, 0x20);
    off_screen_.resize(height * width, 0x20);
}
void jap0_screen::put(int x, int y, char ch) {
    if (y < 0 || height_ < y) {
        return;
    }
    if (x < 0 || width_ < x) {
        return;
    }
    off_screen_[width_ * y + x] = ch;
}

/**
 * @brief ブレゼンハムのアルゴリズムを使用して (x0, y0) から (x1, y1) へ線を描画します。
 * @param x0 始点のx座標
 * @param y0 始点のy座標
 * @param x1 終点のx座標
 * @param y1 終点のy座標
 */
void jap0_screen::drawLine(int x0, int y0, int x1, int y1, char ch) {
    // xとyの変位を計算
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    // xとyの増加方向を決定
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    // 誤差パラメータ
    int err;

    // 傾きによって処理を分岐 (dx >= dy の場合、xを主軸とする)
    if (dx >= dy) {
        // 主軸がxの場合 (傾きが 0 から 1 の間)

        // 最初の誤差パラメータを計算
        err = 2 * dy - dx;
        
        int x = x0;
        int y = y0;

        for (int i = 0; i <= dx; i++) {
            put(x, y, ch); // 現在の点を描画

            // 誤差が0以上の場合、y座標をインクリメント/デクリメントし、誤差を更新
            if (err >= 0) {
                y += sy;
                err -= 2 * dx; // 誤差を dx 分減らす
            }
            // 誤差を dy 分増やす (常に実行される)
            err += 2 * dy;
            
            x += sx; // x座標をインクリメント/デクリメント
        }
    } else {
        // 主軸がyの場合 (傾きが 1 より大きい、または -1 より小さい)
        
        // 最初の誤差パラメータを計算
        err = 2 * dx - dy;

        int x = x0;
        int y = y0;

        for (int i = 0; i <= dy; i++) {
            put(x, y, ch); // 現在の点を描画

            // 誤差が0以上の場合、x座標をインクリメント/デクリメントし、誤差を更新
            if (err >= 0) {
                x += sx;
                err -= 2 * dy; // 誤差を dy 分減らす
            }
            // 誤差を dx 分増やす (常に実行される)
            err += 2 * dx;
            
            y += sy; // y座標をインクリメント/デクリメント
        }
    }
}
void jap0_screen::println(const std::string& line, int x, int y) {
    cur_x_ = x + 1;
    cur_y_ = y + 1;
    if (y < 0 || height_ < y) {
        return;
    }
    int64_t ch64;
    for(int i = 0; i < static_cast<int>(line.size()); i++) {
        char ch = line[i];
        if (ch < 0x80) {
            cur_x_ += 1;
            ch64 = static_cast<int64_t>(ch);
        }
        if ((x + i) < width_) { 
            off_screen_[(y * width_) + x + i] = ch64;
        }
    }
}
void jap0_screen::input(std::string& line) {

}


void jap0_screen::flush(int x, int y) {
    for (int i = 0; i < height_; i++) {
        printf("\e[%d;%dH", 1 + i, 1 + 2);
        for (int j = 0; j < width_; j++) {
            printf("%c", static_cast<char>(off_screen_[i * width_ + j]));
        }
        std::cout << std::endl;
    }
    printf("\e[%d;%dH", cur_x_, cur_y_);
    fflush(stdout);
}
jap0_term::jap0_term() {
    std::cout << "jap0_term" << std::endl;
    struct termios new_termios;
    tcgetattr(STDIN_FILENO, &old_termios);
    new_termios = old_termios;
    new_termios.c_lflag &= ~ICANON;
    new_termios.c_lflag &= ~ECHO;
    new_termios.c_cc[VMIN] = 1;
    new_termios.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

jap0_term::~jap0_term() {
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
    std::cout << "~jap0_term" << std::endl;
}

void jap0_term::get_line(std::string& line) {
    char buf[256];
    std::string mode;
    for (;;) {
        auto ch = getchar();
        if (ch == 0x0a) {
            println(line);
            break;
        } else if (ch == 0x7f) {
            if (line.size() > 0) {
                line.pop_back();
            }
        } else {
            line += ch;
        }
        snprintf(buf, sizeof(buf), "%02x %s", ch, line.c_str());
        std::string p_str(buf);
        println(p_str, -2);
    }
}
void jap0_term::println(std::string& line, int row, int col) {

    auto [heigth, length] = get_term_size();
    if (row == 0 && col == 0) {
        std::cout << line << std::endl;
    } else if (row < 0) {
        std::cout << es_cursor(heigth + 1 + row, col) << line << ERASE_TO_END_OF_LINE;
    } else {
        std::cout << es_cursor(row, col) << line << ERASE_TO_END_OF_LINE;
    }

}

std::tuple<int, int> jap0_term::get_term_size() {
    struct winsize size_ioctl;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size_ioctl) == -1) {
        throw std::runtime_error("");
    }
    cols_ = size_ioctl.ws_col;
    rows_ = size_ioctl.ws_row;
    return std::make_tuple(rows_, cols_);
}

std::string jap0_term::es_cursor(int row, int col){
        std::string result = "\e[5 q\e[";
    result += std::to_string(row);
    result += ";";
    result += std::to_string(col);
    result += "H";
    return result;
}

std::string jap0_term::es_end() {
    return "\e[0m";
}
