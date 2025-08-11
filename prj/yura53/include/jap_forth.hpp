#pragma once
#include "jap.hpp"
#include <map>

class jap_forth : public jap {
    public:
        enum Type {
            SPACE = 1,
            CHAR = 2,
            CTRL = 3,
        };

        virtual ~jap_forth(){}
        std::string help() {
            std::string help;
            help += "-\n";
            help += "jap_forth コマンド\n";
            help += "jap_forth ( jf ) : トップスタックをjap_forchとして処理\n";
            help += "-\n";
            return help;
        }
        bool run(std::string &cmd, std::vector<std::string> &stack);
    private:
        std::map<std::string, std::vector<std::string>> words;
        void forth0(std::vector<std::string> &stack);
        void forth1(std::vector<std::string> &stack);
};
