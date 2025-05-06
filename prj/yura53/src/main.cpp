#include <iostream>
#include <vector>
#include "ivvi.hpp"
#include "markdown.hpp"


int main(int argc, char** argv) {
    std::string str;
    std::vector<std::string> args;

    for (int i = 0; i < argc; ++i) {
        str = argv[i];
        args.push_back(str);
    }
    std::string input_filename;
    std::string output_filename;

    task_mng mng;
    for (auto arg: args) {
        if (arg == "md2html") {
            std::cout << "md2html" << std::endl;
        }
        if (arg == "sqlite") {
            std::cout << "sqlite test" << std::endl;
        }
        if (arg == "ivvi") {
            std::cout << "ivvi" << std::endl;
        }
        if (arg == "markdown") {
            markdown md;
            std::string str_md;

            str_md += "# test\n";
            str_md += "[test]\n";
            

            std::cout << md.html(str_md) << std::endl;
        }
    }
    ivvi iv;
    std::map<std::string, std::string> circle;
    mng.add_task(iv);
    mng.setup();
    mng.loop(circle);
}
