#pragma once

#include "jap.hpp"
#include <regex>
#include "termios.h"

class jap0 : public jap {
public:
    virtual void help() override;
    virtual bool run(const std::string &cmd, std::vector<std::string>& stack) override;

    bool check_line(const std::string& text, std::string& prefix, int& no, std::string& line);
    bool check_pattern(const std::string& text, const std::regex& pattern, std::vector<std::string>& result);

private:
    std::regex line_pattern_ = std::regex(R"(^([0-9]*)\. (.*)$)");
};

class jap0_term {
    struct termios old_termios;
public:
    jap0_term();
    ~jap0_term();

    void get_line(std::string& line);
};
