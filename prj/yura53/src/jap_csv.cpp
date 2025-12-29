#include "jap_csv.hpp"

#include <iostream>

class save_csv_tsv : public jap {
public:
    virtual ~save_csv_tsv() {}
    void help() override {
        std::cout << "-\n";
        std::cout << "ファイル名\n";
        std::cout << "save : スタックの先頭からをファイル名で保存\n";
        std::cout << "-\n";
        std::cout << "save_csv_to_tsv:\n";
        std::cout << "-\n";
        std::cout << "csv_to_tsv:\n";
    }

    bool run(const std::string &cmd, std::vector<std::string> &stack) override  {
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
