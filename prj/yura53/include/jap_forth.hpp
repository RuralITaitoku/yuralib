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
        bool run(const std::string &cmd, std::vector<std::string> &stack);
        std::string pop(std::vector<std::string>& stack, int index = 0);
        // スタックのトップから2番目の値を複製し、スタックのトップに移動
        void over(std::vector<std::string>& stack);
        // スタックのトップにある2つの値の位置を入れ替え
        void swap(std::vector<std::string>& stack);
        // スタックのトップにある3つの値を循環的に移動
        void rot(std::vector<std::string>& stack);
        // スタックのトップにある値を複製
        void dup(std::vector<std::string>& stack);
    private:
        std::map<std::string, std::vector<std::string>> workspace;
        void forth1(std::vector<std::string> &stack);
        void loop();

        void print_map();
        void print_stack(std::vector<std::string> &stack);
};
