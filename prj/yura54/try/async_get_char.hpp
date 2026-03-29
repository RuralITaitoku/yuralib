#pragma once

#include <iostream>
#include <termios.h>

class jap_async {
public:
    struct termios old_termios;
    jap_async();
    ~jap_async();

    bool getChar(int fd, std::string &ch, int usec, bool debug = false);

};

