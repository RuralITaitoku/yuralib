#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <memory>
#include <unistd.h>
#include <sys/wait.h>

class InteractiveProcess {
    pid_t pid_;
    FILE *in_fp_, *out_fp_;

public:
    InteractiveProcess(const std::string& command) {
        int in_pipe[2], out_pipe[2];
        if (pipe(in_pipe) != 0 || pipe(out_pipe) != 0) {
            throw std::runtime_error("Pipe failed");
        }

        pid_ = fork();
        if (pid_ == 0) { // 子プロセス
            dup2(in_pipe[0], STDIN_FILENO);
            dup2(out_pipe[1], STDOUT_FILENO);
            close(in_pipe[1]); close(out_pipe[0]);
            execl("/bin/sh", "sh", "-c", command.c_str(), nullptr);
            _exit(1);
        }

        // 親プロセス
        close(in_pipe[0]); close(out_pipe[1]);
        in_fp_ = fdopen(in_pipe[1], "w");
        out_fp_ = fdopen(out_pipe[0], "r");

        // 行単位で即座に反映させる設定
        setvbuf(in_fp_, nullptr, _IOLBF, 0);
        setvbuf(out_fp_, nullptr, _IOLBF, 0);
    }

    ~InteractiveProcess() {
        if (in_fp_) fclose(in_fp_);
        if (out_fp_) fclose(out_fp_);
        if (pid_ > 0) {
            kill(pid_, SIGTERM);
            waitpid(pid_, nullptr, 0);
        }
    }

    // 1行送る
    void send_line(const std::string& line) {
        fputs((line + "\n").c_str(), in_fp_);
        fflush(in_fp_); 
    }

    // 1行受け取る
    std::string receive_line() {
        char buffer[1024];
        if (fgets(buffer, sizeof(buffer), out_fp_)) {
            return std::string(buffer);
        }
        return "";
    }
};

int main() {
    try {
        // 例: 入力をそのまま加工して返す「bc」(計算機)を対話的に使う
        InteractiveProcess bc("bc -q");

        std::vector<std::string> queries = {"1 + 1", "10 * 5", "scale=2; 7 / 3"};

        for (const auto& q : queries) {
            std::cout << "Send: " << q << std::endl;
            bc.send_line(q);
            
            std::string res = bc.receive_line();
            std::cout << "Recv: " << res; // 改行は含まれている
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
