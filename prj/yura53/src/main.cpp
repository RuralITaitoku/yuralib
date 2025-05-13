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
    std::string template_filename;
    for (int i = 0; i < (args.size() - 1); i++) {
        auto arg = args[i];
        if (arg == "-i") {
            input_filename = args[++i];
        } else if (arg == "-o") {
            output_filename = args[++i];
        } else if (arg == "-t") {
            template_filename = args[++i];
        }
    }
    std::cout << "input : " << input_filename << std::endl;
    std::cout << "output : " << output_filename << std::endl;
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
            auto str_md = yura::load(input_filename);
            auto str_html = md.html(str_md);
            auto str_template = yura::load(template_filename);
            std::cout << str_template << std::endl;
            yura::save(output_filename, yura::replace_all(str_template, "@@@html@@@", str_html));
        }
    }
    ivvi iv;
    std::map<std::string, std::string> circle;
    mng.add_task(iv);
    mng.setup();
    mng.loop(circle);
}
