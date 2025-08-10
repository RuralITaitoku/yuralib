#include "jap_forth.hpp"
#include "yura.hpp"


bool jap_forth::run(std::string &cmd, std::vector<std::string> &stack) {
    if (cmd == "jap_forth" || cmd == "jf") {
        forth(stack);
        return true;
    }
    return false;
}

void jap_forth::forth(std::vector<std::string> &stack) {
    auto jap_stack = words[""];
    std::string cmd;
    for (auto line: stack) {
        size_t start = 0;
        size_t end = line.size();
        std::string word_name;
        size_t word_start = 0;
        for (auto i = start; i < end; ++i) {
            auto ch = line[i];
            if (ch == '.') {
                jap_stack.push_back(cmd);
                jap_stack.push_back(".");
                cmd.clear();
            }
            if (ch == ':') {
                word_name = yura::trim(cmd);
                word_start = jap_stack.size();
                cmd.clear();
            }
            if (ch == ';') {
                auto word_stack = words[word_name];
                for (size_t jap_i = word_start; jap_i < jap_stack.size(); ++jap_i) {
                    word_stack.push_back(jap_stack[jap_i]);
                }
                jap_stack.push_back(";");
                cmd.clear();
            }
        }
    }
}
