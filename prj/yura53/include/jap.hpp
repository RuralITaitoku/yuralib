#ifndef JAP_HPP
#define JAP_HPP

#include <iostream>

class jap {
public:
    virtual std::string help() = 0;
    virtual bool run(std::string &cmd, std::vector<std::string>& stack) = 0;
};

#endif