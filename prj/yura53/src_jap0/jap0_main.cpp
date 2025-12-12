#include <iostream>

#include "jap0.hpp"
#include "yuraterm.hpp"

int main(int argc, char** argv) {
    std::string cmd;
    std::cout << "jap0" << std::endl;
    std::cout << "ssss " << static_cast<int>('\n') << std::endl;
    for (;;) {
        yuraterm term;
        auto result = term.getline();
        std::cout << "結果：" << result << std::endl;
    }
}