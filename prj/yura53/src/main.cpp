#include <iostream>
#include <vector>
#include "ivvi.hpp"

int main(int argc, char** argv) {
    std::string str;
    std::vector<std::string> args;

    for (int i = 0; i < argc; ++i) {
        str = argv[i];
        args.push_back(str);
    }
    std::string input_filename;
    std::string output_filename;

    for (auto arg: args) {
        if (arg == "md2html") {
            std::cout << "md2html" << std::endl;
        }
        if (arg == "sqlite") {
            std::cout << "sqlite test" << std::endl;
        }
        if (arg == "ivvi") {
            std::cout << "ivvi" << std::endl;
            ivvi iv;
        }
    }
}
