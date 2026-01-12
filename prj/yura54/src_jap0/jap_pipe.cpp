#include "jap_pipe.hpp"

#include <memory>

int yura_pipe::exec(const std::string& cmd) {

    std::cout << "コマンド：" << cmd << std::endl;
    std::system(cmd.c_str());
    return 1;
}

std::string yura_pipe::pexec(const std::string& cmd) {
    char buffer[128];     // コマンドの出力を格納するバッファ
    std::string result;

    std::unique_ptr<FILE, int(*)(FILE*)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() に失敗しました！");
    }
    // パイプから出力を読み取り、result に追加していく
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        result += buffer;
    }

    return result;
}
