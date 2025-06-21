#pragma onece
#include <iostream>

class jap {

    virtual std::string help() = 0;
    virtual bool run(std::string &cmd, std::vector<std::string>& stack) == 0;
}