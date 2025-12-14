#include "jap_forth.hpp"
#include "yura.hpp"

template<typename T> class TypeCheck;
#define DP(x) std::cout << __FILE__ << ":" << __LINE__ << " " << x << std::endl;

bool jap_forth::run(const std::string &cmd, std::vector<std::string> &stack) {
    if (cmd == "jap_forth" || cmd == "jf") {
        forth1(stack);
        loop();
        return true;
    }
    return false;
}

void jap_forth::forth1(std::vector<std::string> &stack) {
    DP("jap-forth 1");
    auto& jap_stack = workspace[""];// ルートスタック
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
                    if (!yura::is_all_whitespace(cmd)) {
                        jap_stack.push_back(cmd);
                    }
                    cmd.clear();
                }
                type = SPACE;
            } else if (ch == ':' || ch == ';' || ch == '@'
                || ch == '+' || ch == '-'|| ch == '/'|| ch == '*'
                || ch == '=' || ch == '<'|| ch == '>'|| ch == '!'
                || ch == ',' || ch == '.' ){
                if (type != CTRL) {
                    if (!yura::is_all_whitespace(cmd)) {
                        jap_stack.push_back(cmd);
                    }
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
            if (!yura::is_all_whitespace(cmd)) {
                jap_stack.push_back(cmd);
            }
        }
    }
}

std::string jap_forth::pop(std::vector<std::string>& stack, int index) {
    int  pi = stack.size() - 1 - index;
    if ((pi < 0) || (static_cast<int>(stack.size()) <= pi)) {
        DP("インデックスが範囲外：" << pi);
        DP("stack.size() = " << stack.size());
    }
    auto cmd = stack[pi];
    stack.pop_back();
    return cmd;
}

void jap_forth::print_map() {
    DP("マップの状態");
    for (const auto& pair: workspace) {
        auto body = pair.second;
        std::cout << "name:" << pair.first << std::endl;
        for (auto w: body) {
            std::cout << "- " << w << std::endl;
        }
    }
}
void jap_forth::print_stack(std::vector<std::string> &stack) {
    DP("スタックの状態");
    for (auto cmd: stack) {
        DP("-\"" << cmd << "\"");
    }
}

void jap_forth::loop() {
    DP("ループ");
    std::vector<std::string> stack;
    std::string wd = "";
    auto& jap = workspace[wd];
    print_map();

    for (auto cmd: jap) {
        if (cmd == ".") {
            DP("stack.size = " << stack.size());
            auto str = pop(stack);
            DP("stack.size = " << stack.size());
            std::cout << str << std::endl;
            print_map();
        } else {
            stack.push_back(cmd);
        }
        print_stack(stack);
    }
}