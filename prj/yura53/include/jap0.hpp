#pragma once
#include <iostream>
#include <vector>

class jap0 {
public:
    virtual ~jap0();
    virtual std::string help() = 0;
    virtual int loop(const std::string &cmd, std::vector<std::string>& stack) = 0;
};


jap0_mng  {
    std::vector<std::shared_ptr<jap0>> jap_vec;
    loop(const std::string &cmd, std::vector<std::string> &stack);
}