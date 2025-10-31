#include "jap_zero.hpp"
#include "ivvi.hpp"
#include <cstdlib>

#include <fstream>

std::ofstream debug_log("log.txt");


template<typename T> class TypeCheck;
#define DP(x) std::cout << __FILE__ << ":" << __LINE__ << " " << x << std::endl;

bool jap_zero::run(std::string &cmd, std::vector<std::string> &stack) {
    if (cmd == "jap0" || cmd == "jf") {
    }
    return false;
}

void jap_zero::system(std::string& cmd) {
    std::cout << cmd << std::endl;
    auto result = std::system(cmd.c_str());
    if (result == 0) {
        std::cout << "正常終了" << std::endl;
    } else {
        std::cout << "異常終了:" << result << std::endl;
    }

}

std::string jap_zero::escape(std::string &str) {
    std::string result;

    for (size_t i = 0; i < str.size(); ++i) {
        auto ch = str[i];
        if (ch == '\\') {
            result += ch;
            i++;
        } else if (ch == '"') {
            result += '\\';
            result += ch;
        } else {
            result += ch;
        }
    }
    return result;
}
std::string getWeek(int i) {
    std::vector<std::string> weeks = { "月", "火" , "水", "木", "金", "土", "日"};
    return weeks[i % 7];
}

void jap_zero::main() {
    std::string git_cmd("git pull");
    system(git_cmd);
    std::string line;
    std::vector<std::string> stack;
    std::cout << "-"  << std::endl;
    for(;;) {
        getline(std::cin, line);
        if (line == ".") {
            if (stack.size()) {
                std::cout << stack.back() << std::endl;
                stack.pop_back();
            }
        } else if (line == "..") {
            std::cout << "-stack-" << stack.size() << std::endl;
            if (stack.size()) {
                for (size_t i = 0; i < stack.size(); i++) {
                    std::cout << i << ":" << stack[i] << std::endl;
                }
            }
            std::cout << "-" << std::endl;
        } else if (line == "clear") {
            stack.clear();
        } else if (line == "drop") {
            if (stack.size()) {
                stack.pop_back();
            }
        } else if (line == "s" || line == "status") {
            git_cmd = "git status";
            system(git_cmd);
        } else if (line == "d" || line == "diff") {
            git_cmd = "git diff";
            system(git_cmd);
        } else if (line == "a" || line == "add") {
            git_cmd = "git add .;git status";
            system(git_cmd);
        } else if (line == "b" || line == "branch") {
            git_cmd = "git branch -a -vv";
            system(git_cmd);
        } else if (line == "c" || line == "commit") {
            git_cmd = "git commit -m \"";
            auto msg = stack.back();
            git_cmd += escape(msg);
            git_cmd += '\"';
            system(git_cmd);
        } else if (line == "iv") {
            std::cout << "iv" << std::endl;
            ivvi edit;
            edit.run(line, stack);
        } else if (line == "td") {
            auto ymd = yura::today();
            for (int i = 0; i < 33; i++){
                std::string str = std::to_string(ymd/10000)
                    + "年" + std::to_string(ymd/100 % 100)
                    + "月" + std::to_string(ymd % 100) + "日(" + getWeek(i) + ")";
                stack.push_back(str);
                ymd = yura::add_days(ymd, 1);
            }
                //ivvi(line, stack);
        } else if (line == "p" || line == "push") {
            git_cmd = "git push";
            system(git_cmd);
        } else if (line == "q") {
                std::cout << "jap終了" << std::endl;
            return;
        } else {
            
            stack.push_back(line);
        }
    }
}

int main() {
    std::cout << "jap" << std::endl;
    jap_zero jap0;

    jap0.main();
}