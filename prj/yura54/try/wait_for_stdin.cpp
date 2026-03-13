#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>

void wait_for_stdin() {
    fd_set readfds;
    struct timeval timeout;
    int retval;

    // 1. 監視するファイル記述子のセットをクリア
    FD_ZERO(&readfds);
    // 2. 標準入力 (stdin = 0) をセットに登録
    FD_SET(0, &readfds);

    // 3. タイムアウト時間を設定 (5秒)
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    printf("5秒以内に入力してください...\n");

    // 4. selectを呼び出す
    // 第1引数は監視する最大のFD番号 + 1
    retval = select(1, &readfds, NULL, NULL, &timeout);

    if (retval == -1) {
        perror("select()");
    } else if (retval) {
        // 5. データが届いた場合
        if (FD_ISSET(0, &readfds)) {
            char buf[1024];
            int len = read(0, buf, sizeof(buf) - 1);
            buf[len] = '\0';
            printf("読み込んだデータ: %s", buf);
        }
    } else {
        // 6. タイムアウト（5秒経過）
        printf("タイムアウト：入力がありませんでした。\n");
    }
}

int main() {
    for (;;) {
        wait_for_stdin();
    }
    return 0;
}
