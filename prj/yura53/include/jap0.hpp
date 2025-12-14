#pragma once

#include "jap.hpp"

class jap0 : public jap {
public:
    virtual std::string help() override;
    virtual bool run(const std::string &cmd, std::vector<std::string>& stack) override;

    bool check_line(const std::string& text, std::string& prefix, int& no, std::string& line);

private:
    std::string row_cmd;
    std::string row_line;

};


