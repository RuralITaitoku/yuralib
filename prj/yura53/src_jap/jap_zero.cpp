#include "jap_zero.hpp"
#include <cstdlib>
template<typename T> class TypeCheck;
#define DP(x) std::cout << __FILE__ << ":" << __LINE__ << " " << x << std::endl;

bool jap_zero::run(std::string &cmd, std::vector<std::string> &stack) {
    if (cmd == "jap0" || cmd == "jf") {
    }
    return false;
}
void jap_zero::main() {
    std::string line;
    std::vector<std::string> stack;
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
            auto result = std::system("git status");
            if (result == 0) {
                std::cout << "正常終了" << std::endl;
            } else {
                std::cout << "異常終了:" << result << std::endl;
            }
        } else if (line == "commit") {
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