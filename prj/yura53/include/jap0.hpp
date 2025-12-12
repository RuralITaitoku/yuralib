#pragma once

#include "jap.hpp"

class jap0 : public jap {
public:
    virtual std::string help() override;
    virtual bool run(const std::string &cmd, std::vector<std::string>& stack) override;

};


