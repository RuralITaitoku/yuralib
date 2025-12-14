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
        std::string help() {
            std::string help;
            help += "-\n";
            help += "jap_forth コマンド\n";
            help += "jap_forth ( jf ) : トップスタックをjap_forchとして処理\n";
            help += "-\n";
            return help;
        }
        bool run(const std::string &cmd, std::vector<std::string> &stack);
        void system(std::string &cmd);
        std::string escape(std::string &str);
        void main();
    private:
};
