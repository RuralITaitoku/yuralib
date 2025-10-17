#pragma once
#include "jap.hpp"


class ivvi : public jap {
public:
    ivvi();
    ~ivvi();
    virtual std::string help();
    virtual bool run(std::string &cmd, std::vector<std::string>& stack);

    int print(const std::string &str, int fg, int bg);
};