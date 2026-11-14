#pragma once
#include "jap.hpp"
#include <map>
#include "yuraterm.hpp"


class jap_zero : public jap {
    public:
        enum Type {
            SPACE = 1,
            CHAR = 2,
            CTRL = 3,
        };

        virtual ~jap_zero(){}
        void help() override {
            std::cout << "-\n";
            std::cout << "jap_forth コマンド\n";
            std::cout << "jap_forth ( jf ) : トップスタックをjap_forchとして処理\n";
            std::cout << "-\n";
        }
        bool run(const std::string &cmd, std::vector<std::string> &stack) override ;
        void system(std::string &cmd);
        std::string escape(std::string &str);
        void main();
    private:
};
