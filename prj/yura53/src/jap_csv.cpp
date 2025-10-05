#include "jap_csv.hpp"

#include <iostream>

class save_csv_tsv : public jap {
public:
    virtual ~save_csv_tsv() {}
    std::string help() {
        std::string help;
        help += "-\n";
        help += "ファイル名\n";
        help += "save : スタックの先頭からをファイル名で保存\n";
        help += "-\n";
        help += "save_csv_to_tsv:\n";
        help += "-\n";
        help += "csv_to_tsv:\n";
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
        if (cmd == "csv_to_tsv") {
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
        if (cmd == "save_csv_to_tsv") {
            std::cout << "セーブな感じtsv" << std::endl;
            return true;
        }
        return false;
    }
};
