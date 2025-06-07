#include <iostream>
#include <vector>
#include "ivvi.hpp"
#include "markdown.hpp"

void jap_notation() {
    std::cout << "jap notation" << std::endl;
    std::string line;
    std::vector<std::string> stack;

    for (;;) {
        std::cin >> line;
        std::cout << "-" << line << std::endl;
        if (line == "") {
            std::cout << "--- help" << std::endl;
            std::cout << "ps : print stack" << std::endl;
            std::cout << "cs : clear stack" << std::endl;
        } else if (line == "ps") {
            std::cout << "--- print stack" << std::endl;
            int no = 0;
            for (auto l: stack) {
                std::cout << no++ << ":";
                std::cout << l << std::endl;
            }
        } else if (line == "cs") {
            std::cout << "--- clear stack" << std::endl;
            stack.clear();

        } else if (line == "q") {
            std::cout << "--- quit" << std::endl;
            return;
        } else {
            stack.push_back(line);
        }
    }
}


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
    // DP("input : " << input_filename);
    // DP("output : " << output_filename);
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
            //std::cout << str_template << std::endl;
            yura::save(output_filename, yura::replace_all(str_template, "@@@html@@@", str_html));
        }
        if (arg == "jap") {
            jap_notation();
        }
    }
}


