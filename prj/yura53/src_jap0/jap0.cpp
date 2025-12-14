#include "jap0.hpp"

#include<regex>

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
    std::regex line_pattern(R"(^([0-9]*)\. (.*)$)");
    std::smatch matches;
    if (std::regex_search(src, matches, line_pattern)) {
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


std::string jap0::help() {
    std::string result;
    result += "jap0::help!!!!!!!!!!!!!!!!";
    return result;
}
bool jap0::run(const std::string& cmd, std::vector<std::string>& stack) {
    if (cmd == "jap0") {
        std::cout << "jap0 test" << std::endl;
        return true;
    }
    return false;
}


