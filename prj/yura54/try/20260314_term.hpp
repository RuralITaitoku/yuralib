#pragma once

#include <iostream>

class term {
public:
    term(){};
    ~term(){};

    bool getLine(int fd, std::string &line);

};

