#pragma once
#include "jap.hpp"
#include <map>

class jap_forth : public jap {
    public:

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
        void forth(std::vector<std::string> &stack);
};
