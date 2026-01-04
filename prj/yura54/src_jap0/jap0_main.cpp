#include <iostream>

#include "jap0.hpp"
#include <regex>


int main(int argc, char** argv) {
    std::string cmd;
    jap0_term term;

    std::vector<std::string> stack;
    std::vector< std::shared_ptr<jap> > japs;
    japs.push_back(std::make_shared<jap0>());
    for (;;) {
        // std::getline(std::cin, cmd);
        cmd = "";
        term.get_line(cmd);
        if (cmd == "") {
        } else if (cmd == "q") {
            break;
        } else if (cmd == "..") {
            for (size_t i = 0; i < stack.size(); i++) {
                std::cout << i << ". " << stack[i] << std::endl;
            }
            std::cout << "--- " << stack.size() << std::endl;
        } else if (cmd == "clear") {
            stack.clear();
        } else if (cmd == "test") {
            std::string input = "input test";
            jap0_screen screen;
            screen.init(80, 20);
            screen.put(2, 2, '@');
            screen.println("test hisadomi", 1, 3);
            screen.flush(6, 6);
        } else if (cmd == "help") {
            for (auto jap : japs) {
                jap->help();
            }
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