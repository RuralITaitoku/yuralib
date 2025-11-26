#pragma once
#include <iostream>
#include <vector>
#include <memory> 

class jap0 {
public:
    virtual ~jap0();
    virtual std::string help() = 0;
    virtual int loop(const std::string &cmd, std::vector<std::string>& stack) = 0;
};


class jap0_mng  {
    std::vector<std::shared_ptr<jap0>> jap_vec;
    int loop(const std::string &cmd, std::vector<std::string> &stack);
};