#pragma once
#include "task.hpp"


class ivvi : public task {
public:
    ivvi();
    ~ivvi();
    virtual void setup();
    virtual int loop(std::map<std::string, std::string>& circle);
};