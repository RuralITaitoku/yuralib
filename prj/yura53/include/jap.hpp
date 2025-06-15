#pragma onece
#include <iostream>

class jap {

    virtual std::string name() = 0;
    virtual std::string help() = 0;
    virtual int loop(std::vector<std::string>& stack) == 0;
}