#include <iostream>
#include <iostream>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include "20260314_term.hpp"

term::term() {
    tcgetattr(STDIN_FILENO, &old_termios);
    struct termios new_termios;
    new_termios = old_termios;
    new_termios.c_lflag &= ~ICANON;
    new_termios.c_lflag &= ~ECHO;
    new_termios.c_cc[VMIN] = 1;
    new_termios.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

term::~term() {
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
}

bool term::getChar(int fd, std::string &ch) {
    fd_set readfds;
    struct timeval timeout;

    // std::cout << "1秒以内に何か入力してエンターを押してください..." << std::endl;

    // 1. 監視対象のセットをクリアし、標準入力を登録
    FD_ZERO(&readfds);
    FD_SET(0, &readfds);

    // 2. タイムアウト時間を1秒に設定
    timeout.tv_sec = 0;
    timeout.tv_usec = 10000;

    // 3. selectの実行
    // 第1引数は「最大ファイル記述子 + 1」なので、0 + 1 = 1
    int retval = select(1, &readfds, NULL, NULL, &timeout);

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
            // printf("読み込んだデータ: %s", buf);
        }
        for (int i = 0; i < ch.size(); ++i) {
            printf("%02x", ch[i]);
        }
        std::cout << std::endl;
        // std::cout << "入力された内容: " << ch << std::endl;
        return false;
    } else {
        // タイムアウト（retval == 0）
        std::cout << "-" << std::endl;
        return true;
    }
}


int main() {
    std::cout << "term test" << std::endl;
    term t;
    std::string line;
    for (;;) {
        t.getChar(0, line);
    }
    return 0;
}
