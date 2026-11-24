#include <stdio.h>
#include <errno.h>
#include <poll.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

/**
 * @brief タイムアウト付きで文字を1文字読み込む（Linux / POSIX）
 *
 * 標準入力を一時的に非カノニカル・エコー無効モードに切り替えて、
 * 指定されたミリ秒数の間、1文字の入力を待機します。
 * 読み込んだ後は必ず元の端末設定へ復元します。
 *
 * @param timeout 入力を待機するタイムアウト時間（ミリ秒）。
 *                0 を指定すると即時チェック（非ブロッキング相当）、
 *                負の値を指定すると入力があるまで無期限に待機します。
 *
 * @return 読み込んだ文字の値（`unsigned char` から `int` へ変換した 0〜255 の値）。
 *         タイムアウト時は `-1`（`errno` は変化しない場合あり）、
 *         EOF またはシステムコールエラー時は `-1`（エラー時は `errno` が設定される）を返します。
 */
int getch_with_timeout(int timeout)
{
    struct termios old_tio, new_tio;

    if (tcgetattr(STDIN_FILENO, &old_tio) != 0) {
        return -1;
    }

    new_tio = old_tio;
    /* カノニカルモード（行バッファリング）とエコーを無効化 */
    new_tio.c_lflag &= (tcflag_t)~(ICANON | ECHO);
    new_tio.c_cc[VMIN] = 1;
    new_tio.c_cc[VTIME] = 0;

    if (tcsetattr(STDIN_FILENO, TCSANOW, &new_tio) != 0) {
        return -1;
    }

    struct pollfd pfd;
    pfd.fd = STDIN_FILENO;
    pfd.events = POLLIN;
    pfd.revents = 0;

    int ret;
    do {
        ret = poll(&pfd, 1, timeout);
    } while (ret < 0 && errno == EINTR);

    int result = -1;

    if (ret > 0 && (pfd.revents & POLLIN)) {
        unsigned char ch;
        ssize_t n;
        do {
            n = read(STDIN_FILENO, &ch, 1);
        } while (n < 0 && errno == EINTR);

        if (n == 1) {
            result = (int)ch;
        }
    }

    /* 元の端末設定を復元（errno を保持） */
    int saved_errno = errno;
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
    errno = saved_errno;

    return result;
}

#ifdef DEBUG

int main(int argc, char** argv) {
    for (;;) {
        int ch = getch_with_timeout(999);
        printf("%c\n", (char)ch);
        if ((char)ch == 'q') {
            break;
        }
    }
}


#endif
