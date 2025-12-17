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



jap0_term::jap0_term() {

}

jap0_term::~jap0_term() {

}

void jap0_term::get_line(std::string& line) {
}