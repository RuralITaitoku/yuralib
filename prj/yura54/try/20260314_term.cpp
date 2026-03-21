#include <iostream>
#include <iostream>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>

#include "20260314_term.hpp"


bool term::getChart(int fd, std::string &ch) {
    fd_set readfds;
    struct timeval timeout;

    std::cout << "1秒以内に何か入力してエンターを押してください..." << std::endl;

    // 1. 監視対象のセットをクリアし、標準入力を登録
    FD_ZERO(&readfds);
    FD_SET(0, &readfds);

    // 2. タイムアウト時間を1秒に設定
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    // 3. selectの実行
    // 第1引数は「最大ファイル記述子 + 1」なので、0 + 1 = 1
    int retval = select(1, &readfds, NULL, NULL, &timeout);

    if (retval == -1) {
        perror("select()");
        return false;
    } else if (retval) {
        // 入力があった場合
        ch.clear();
        std::cin >> ch;
        std::cout << "入力された内容: " << ch << std::endl;
        return false;
    } else {
        // タイムアウト（retval == 0）
        std::cout << "タイムアウト：1秒間入力がありませんでした。" << std::endl;
        return true;
    }
}


int main() {
    std::cout << "term test" << std::endl;
    term t;
    std::string line;
    t.getLine(0, line);
    return 0;
}
