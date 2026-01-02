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


void jap0_screen::init(int rows, int cols) {
    rows_ = rows;
    cols_ = cols;
    screen_.resize(rows * cols, 0x20);
    off_screen_.resize(rows * cols, 0x20);
}
void jap0_screen::put(int row, int col, char ch) {
    if (row < 0 || rows_ < row) {
        return;
    }
    if (col < 0 || cols_ < col) {
        return;
    }
    off_screen_[cols_ * row + col] = ch;
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
