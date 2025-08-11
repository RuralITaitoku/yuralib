#include "jap_forth.hpp"
#include "yura.hpp"

template<typename T> class TypeCheck;
#define DP(x) std::cout << __FILE__ << ":" << __LINE__ << " " << x << std::endl;

bool jap_forth::run(std::string &cmd, std::vector<std::string> &stack) {
    if (cmd == "jap_forth" || cmd == "jf") {
        forth1(stack);
        loop();
        return true;
    }
    return false;
}

std::string jap_forth::pop(std::vector<std::string>& stack) {
    std::string result = stack.back();
    stack.pop_back();
    return result;
}


void jap_forth::forth1(std::vector<std::string> &stack) {
    DP("jap-forth 1");
    auto& jap_stack = words[""];// ルートスタック
    jap_stack.clear();
    //TypeCheck<decltype(jap_stack)> check;
    std::string cmd;
    auto type = SPACE;
    for (auto line: stack) {
        size_t start = 0;
        size_t end = line.size();
        std::string cmd;
        for (auto i = start; i < end; ++i) {
            auto ch = line[i];
            if ((ch == ' ') ||
                (ch == '\t') ||
                (ch == '\r') ||
                (ch == '\n'))  {
                if (type == SPACE) {
                    cmd.push_back(ch);
                } else {
                    jap_stack.push_back(cmd);
                    cmd.clear();
                }
                type = SPACE;
            } else if (ch == ':' || ch == ';' || ch == '@'
                || ch == '+' || ch == '-'|| ch == '/'|| ch == '*'
                || ch == '=' || ch == '<'|| ch == '>'|| ch == '!'
                || ch == ',' || ch == '.' ){
                if (type != CTRL) {
                    jap_stack.push_back(cmd);
                    cmd.clear();
                }
                cmd.push_back(ch);
                type = CTRL;
            } else {
                cmd.push_back(ch);
                type = CHAR;
            }
        }
        if (!cmd.empty()) {
            jap_stack.push_back(cmd);
        }
    }
}

void jap_forth::loop() {
    DP("ループ");
    DP("マップの状態");
    for (const auto& pair: words) {
        auto body = pair.second;
        std::cout << "name:" << pair.first << std::endl;
        for (auto w: body) {
            std::cout << "- " << w << std::endl;
        }
    }
}