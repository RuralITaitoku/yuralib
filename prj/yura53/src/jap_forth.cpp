#include "jap_forth.hpp"
#include "yura.hpp"

template<typename T> class TypeCheck;
#define DP(x) std::cout << __FILE__ << ":" << __LINE__ << " " << x << std::endl;

bool jap_forth::run(std::string &cmd, std::vector<std::string> &stack) {
    if (cmd == "jap_forth" || cmd == "jf") {
        std::cout << "jap_forth" << std::endl;
        forth(stack);
        return true;
    }
    return false;
}

void jap_forth::forth(std::vector<std::string> &stack) {
    auto& jap_stack = words[""];// ルートスタック
    //TypeCheck<decltype(jap_stack)> check;
    std::string cmd;
    for (auto line: stack) {
        size_t start = 0;
        size_t end = line.size();
        std::string word_name = "";
        size_t word_start = 0;
        bool space = true;
        for (auto i = start; i < end; ++i) {
            auto ch = line[i];
            if (ch == '.') {
                jap_stack.push_back(cmd);
                jap_stack.push_back(".");
                cmd.clear();
            } else if (ch == ':') {
                word_name = yura::trim(cmd);
                word_start = jap_stack.size();
                auto& word_stack = words[word_name];
                word_stack.clear();
                cmd.clear();
            } else if (ch == ';') {
                jap_stack.push_back(yura::trim(cmd));
                jap_stack.push_back(";");
                auto& word_stack = words[word_name];
                for (size_t jap_i = word_start; jap_i < jap_stack.size(); ++jap_i) {
                    auto jw = jap_stack[jap_i];
                    if (!yura::is_all_whitespace(jw)) {
                        word_stack.push_back(jw);
                    }
                }
                DP("word_start:" << word_start);
                DP("word_name:" << word_name);
                jap_stack.erase(jap_stack.begin() + word_start, jap_stack.end());
                jap_stack.push_back(word_name);
                for (auto jap: jap_stack) {
                    std::cout << jap << std::endl;
                }
                DP("マップの状態");
                for (const auto& pair: words) {
                    auto body = pair.second;
                    std::cout << "name:" << pair.first << std::endl;
                    for (auto w: body) {
                        std::cout << "- " << w << std::endl;
                    }
                }
                DP("");
                cmd.clear();
            } else if ((ch == ' ') ||
                        (ch == '\t') ||
                        (ch == '\r') ||
                        (ch == '\n'))  {
                if (!space) {
                    jap_stack.push_back(cmd);
                }
                space = true;
                cmd.clear();
            } else {
                cmd.push_back(ch);
                space = false;
            }
        }
    }
}
