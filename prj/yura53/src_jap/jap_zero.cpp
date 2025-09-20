#include "jap_zero.hpp"
#include <cstdlib>
template<typename T> class TypeCheck;
#define DP(x) std::cout << __FILE__ << ":" << __LINE__ << " " << x << std::endl;

bool jap_zero::run(std::string &cmd, std::vector<std::string> &stack) {
    if (cmd == "jap0" || cmd == "jf") {
    }
    return false;
}

void jap_zero::system(std::string& cmd) {
    auto result = std::system(cmd.c_str());
    if (result == 0) {
        std::cout << "正常終了" << std::endl;
    } else {
        std::cout << "異常終了:" << result << std::endl;
    }

}

void jap_zero::main() {
    std::cout << "git pull" << std::endl;
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
        } else if (line == "a" || line == "add") {
            git_cmd = "git add .;git status";
            system(git_cmd);
        } else if (line == "commit") {
        } else if (line == "p" || line == "push") {
            git_cmd = "git push;git status";
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