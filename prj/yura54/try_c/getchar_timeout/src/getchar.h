#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>

// ターミナルの設定を変更（1文字単位で即時入力できるようにする）
void set_raw_mode(struct termios *orig_termios);

// ターミナルの設定を元に戻す
void restore_mode(struct termios *orig_termios);

// タイムアウト付き1文字入力（タイムアウト時は -1 を返す）
int getchar_timeout(int seconds) {
    fd_set set;
    struct timeval timeout;

    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);

    timeout.tv_sec = seconds;
    timeout.tv_usec = 0;

    // 標準入力(STDIN_FILENO)に入力があるか監視
    int rv = select(STDIN_FILENO + 1, &set, NULL, NULL, &timeout);

    if (rv > 0) {
        // 入力があった場合、1バイト読み込む
        char ch;
        if (read(STDIN_FILENO, &ch, 1) == 1) {
            return (unsigned char)ch;
        }
    }
    
    // タイムアウト(rv == 0) または エラー(rv == -1)
    return -1;
}

int main() {
    struct termios orig_termios;

    // ターミナルを1文字入力モードに変更
    set_raw_mode(&orig_termios);

    printf("3秒以内に何かキーを押してください (Enter不要): ");
    fflush(stdout);


    int c;

    while ((c = getchar_timeout(1)) == -1) {
        printf("timeout!\n");
    }

    // ターミナルの設定を必ず元に戻す
    restore_mode(&orig_termios);

    if (c != -1) {
        printf("\n入力された文字: '%c' (ASCII: %d)\n", c, c);
    } else {
        printf("\nタイムアウトしました。\n");
    }

    return 0;
}
