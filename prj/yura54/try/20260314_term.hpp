#pragma once

#include <iostream>
#include <termios.h>

class term {
public:
    struct termios old_termios;
    term();
    ~term();

    bool getChar(int fd, std::string &ch);

};

