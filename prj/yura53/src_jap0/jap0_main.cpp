#include <iostream>

#include "jap0.hpp"
#include "yuraterm.hpp"
#include <regex>

bool check_line(const std::string& text, std::string& prefix, int& no, std::string& line) {
    std::string src;
    if (text.empty()) {
        return false;
    }
    if (text[0] == 'a') {
        prefix = "a";
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

int main(int argc, char** argv) {
    std::string cmd;
    int row_no;
    std::string row_cmd;
    std::string row_line;

    std::vector<std::string> stack;
    std::vector< std::shared_ptr<jap> > japs;
    japs.push_back(std::make_shared<jap0>());
    for (;;) {
        std::getline(std::cin, cmd);
        if (cmd == "q") {
            break;
        } else if (cmd == "..") {
            for (size_t i = 0; i < stack.size(); i++) {
                std::cout << i << ". " << stack[i] << std::endl;
            }
            std::cout << "--- " << stack.size() << std::endl;
        } else if (cmd == "clear") {
            stack.clear();
        } else if (cmd == "help") {
            for (auto jap : japs) {
                std::cout << jap->help() << std::endl;
            }
        } else if (check_line(cmd, row_cmd, row_no, row_line)) {
            std::cout << row_cmd << " " << row_no << ". " << row_line << std::endl;
        } else {
            bool run_flag = false;
            for (auto jap : japs) {
                run_flag = jap->run(cmd, stack);
                if (run_flag) break;
            }
            if (!run_flag) {
                stack.push_back(cmd);
            }
        }
    }
}