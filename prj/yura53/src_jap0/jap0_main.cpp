#include <iostream>

#include "jap0.hpp"
#include "yuraterm.hpp"

int main(int argc, char** argv) {
    std::string cmd;
    std::cout << "jap0" << std::endl;
    std::cout << "ssss " << static_cast<int>('\n') << std::endl;
    for (;;) {
        std::getline(std::cin, cmd);


        std::cout << "jap0 cmd=" << cmd << std::endl;
        if (cmd == "test") {
            std::cout << "test" << std::endl;
            yuraterm term;
            auto test = term.getline();
        }
        break;
    }

}