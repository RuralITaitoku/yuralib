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
        help += "ファイル名\n";
        help += "save : スタックの先頭からをファイル名で保存\n";
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

class dialy_jap : public jap {
public:
    virtual ~dialy_jap() {}
    std::string help() {
        std::string help;
        help += "-\n";
        help += "today : 今日の日付を整数でスタック。\n";
        help += "-\n";
        help += "開始日(整数)から\n";
        help += "終了日(整数)まで\n";
        help += "make ymd link : 日付リンクのソースを作る❓\n";
        return help;
    }

    bool run(std::string &cmd, std::vector<std::string> &stack) {
        if (cmd == "today") {
            int ymd = yura::today();
            stack.push_back(std::to_string(ymd));
            return true;
        }
        return false;
    }
};

class shell_jap : public jap {
public:
    virtual ~shell_jap() {}
    std::string help() {
        std::string help;
        help += "-\n";
        help += "シェルコマンド\n";
        help += ". : シェルコマンド実行❓\n";
        return help;
    }

    bool run(std::string &cmd, std::vector<std::string> &stack) {
        if (cmd == ".") {
            auto cmd = stack.back();
            stack.pop_back();
            std::cout << cmd << std::endl;
            return true;
        }
        return false;
    }
};


void jap_notation() {
    std::cout << "jap notation" << std::endl;
    std::string line;
    std::vector<std::string> stack;

    jap_vec.push_back(std::make_shared<save_csv_tsv>());
    jap_vec.push_back(std::make_shared<dialy_jap>());
    jap_vec.push_back(std::make_shared<shell_jap>());
    for (;;) {
        std::getline(std::cin, line);
        //std::cout << "-" << line << std::endl;
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
    std::string replace_word = "@@@html@@@";
    for (size_t i = 0; i < (args.size() - 1); i++) {
        auto arg = args[i];
        if (arg == "-i") {
            input_filename = args[++i];
        } else if (arg == "-o") {
            output_filename = args[++i];
        } else if (arg == "-t") {
            template_filename = args[++i];
        } else if (arg == "-rw") {
            replace_word = args[++i];
        }
    }
    // DP("input : " << input_filename);
    // DP("output : " << output_filename);
    // DP("replace_word : " << replace_word);
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
            yura::save(output_filename, yura::replace_all(str_template, replace_word, str_html));
        }
        if (arg == "jap") {
            jap_notation();
        }
    }
}


