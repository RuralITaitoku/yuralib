#pragma once
#include <iostream>
#include <string>
#include <cstdio>


class yura_pipe {

 
    public:
    int exec(const std::string& cmd);
    std::string pexec(const std::string& cmd);

};