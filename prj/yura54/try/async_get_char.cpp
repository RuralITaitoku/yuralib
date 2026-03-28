#include <iostream>
#include <iostream>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include "async_get_char.hpp"

jap_async::jap_async() {
    tcgetattr(STDIN_FILENO, &old_termios);
    struct termios new_termios;
    new_termios = old_termios;
    new_termios.c_lflag &= ~ICANON;
    new_termios.c_lflag &= ~ECHO;
    new_termios.c_cc[VMIN] = 1;
    new_termios.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

jap_async::~jap_async() {
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
}

bool jap_async::getChar(int fd, std::string &ch, bool debug) {
    fd_set readfds;
    struct timeval timeout;

    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);

    timeout.tv_sec = 1;
    timeout.tv_usec = 10000;

    auto max_fd = fd;
    int retval = select(max_fd + 1, &readfds, NULL, NULL, &timeout);

    if (retval == -1) {
        perror("select()");
        return false;
    } else if (retval) {
        // 入力があった場合
        ch.clear();
        if (FD_ISSET(0, &readfds)) {
            char buf[1024];
            int len = read(0, buf, sizeof(buf) - 1);
            buf[len] = '\0';
            ch = buf;
        }
        printf("\e[0;0H");
        for (int i = 0; i < ch.size(); ++i) {
            if (ch[i] < 0x20) {
                printf(" %02x", ch[i]);
            } else {
                printf(" %02x(%c)", ch[i], ch[i]);
            }
        }
        std::cout << "\e[0K" << std::endl;
        return false;
    } else {
        return true;
    }

}

int main(int argc, char **argv) {
    jap_async async;

    std::string ch;
    for (;;) {
       async.getChar(0, ch, true); 
    }
}

