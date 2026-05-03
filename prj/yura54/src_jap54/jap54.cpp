#include "jap54.hpp"
#include <sys/epoll.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdexcept>
#include <string>
#include <cerrno>

// STDIN を O_NONBLOCK に設定するユーティリティ
static void jap54::set_nonblocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1)
        throw std::runtime_error("fcntl F_GETFL failed");
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
        throw std::runtime_error("fcntl F_SETFL failed");
}

// 呼び出し前に set_nonblocking(STDIN_FILENO) を一度だけ呼ぶ想定
std::string jap54::readline_epoll_nb(int epfd, int timeout_ms = -1) {
    epoll_event events[1];
    std::string line;
    char buf[256];

    while (true) {
        // ① イベント待機（ここは O_NONBLOCK でもブロックする）
        int n = epoll_wait(epfd, events, 1, timeout_ms);
        if (n == -1)
            throw std::runtime_error("epoll_wait failed");
        if (n == 0)
            throw std::runtime_error("timeout");

        if (!(events[0].events & EPOLLIN))
            throw std::runtime_error("epoll error event");

        // ② EAGAIN になるまでバッファをまとめて読む
        while (true) {
            ssize_t r = read(STDIN_FILENO, buf, sizeof(buf));

            if (r == 0)          // EOF
                return line;

            if (r == -1) {
                if (errno == EAGAIN || errno == EWOULDBLOCK)
                    break;       // ③ データ枯渇 → epoll_wait に戻る
                throw std::runtime_error("read failed");
            }

            // ④ バッファ内を '\n' でスキャン
            for (ssize_t i = 0; i < r; ++i) {
                if (buf[i] == '\n')
                    return line;  // 行完成
                line += buf[i];
            }
        }
    }
}
/**
int main() {
    set_nonblocking(STDIN_FILENO);

    // epfd はプログラム起動時に一度だけ作る
    int epfd = epoll_create1(0);
    epoll_event ev{};
    ev.events = EPOLLIN;
    ev.data.fd = STDIN_FILENO;
    epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &ev);

    try {
        std::string line = readline_epoll_nb(epfd, 5000);
        // line を使う処理...
    } catch (const std::exception& e) {
        // エラー処理
    }

    close(epfd);
}*/
