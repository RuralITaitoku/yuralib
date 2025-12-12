#include <iostream>

#include "jap0.hpp"
#include "yuraterm.hpp"

int main(int argc, char** argv) {
    std::string cmd;

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
        } else {
            bool run_flag = false;
            for (auto jap : japs) {
                run_flag |= jap->run(cmd, stack);
            }
            if (!run_flag) {
                stack.push_back(cmd);
            }
        }

    }

}