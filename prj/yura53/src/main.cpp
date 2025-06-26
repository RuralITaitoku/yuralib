#include "ivvi.hpp"
#include "markdown.hpp"
#include "jap.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <sstream>

std::vector<std::shared_ptr<jap>> jap_vec;

class save_csv_tsv : public jap {
public:
    virtual ~save_csv_tsv() {}
    std::string help() {
        std::string help;
        help += "-\n";
        help += "スタック先頭～\n";
        help += "ファイル名\n";
        help += "save : スタックの先頭からファイル名までを保存\n";
        help += "-\n";
        help += "save csv to tsv:\n";
        help += "-\n";
        help += "csv to tsv:\n";
        return help;
    }

    bool run(std::string &cmd, std::vector<std::string> &stack) {
        if (cmd == "save") {
            auto filename = stack.back();
            stack.pop_back();
            std::cout << "filename=" << filename << std::endl;
            std::ostringstream oss;
            for (auto line: stack) {
                oss << line << std::endl;
            }
            yura::save(filename, oss.str());
            return true;
        }
        if (cmd == "csv to tsv") {
            for (size_t i = 0; i < stack.size(); i++) {
                auto vec = yura::split(stack[i], ",");
                std::string result;
                for (auto a: vec) {
                    result += yura::trim(a);
                    result += "\t";
                }
                stack[i] = result;
            }
            return true;
        }
        if (cmd == "save csv to tsv") {
            std::cout << "セーブな感じtsv" << std::endl;
            return true;
        }
        return false;
    }
};


void jap_notation() {
    std::cout << "jap notation" << std::endl;
    std::string line;
    std::vector<std::string> stack;

    auto jap0 = std::make_shared<save_csv_tsv>();
    jap_vec.push_back(jap0);
    for (;;) {
        std::getline(std::cin, line);
        std::cout << "-" << line << std::endl;
        if (line == "" || line == "h") {
            std::cout << "--- help" << std::endl;
            std::cout << "ps : print stack" << std::endl;
            std::cout << "cs : clear stack" << std::endl;
            for (auto jap : jap_vec) {
                std::cout << jap->help();
            }
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
            bool f_run = false;
            for (auto jap : jap_vec) {
                if(jap->run(line, stack)) {
                    f_run = true;
                    break;
                }
            }

            if (!f_run) {
                std::cout << "stackkkk" << std::endl;
                stack.push_back(line);
            }
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
    for (size_t i = 0; i < (args.size() - 1); i++) {
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


