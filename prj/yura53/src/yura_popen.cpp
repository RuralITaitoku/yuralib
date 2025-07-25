#include "yura_popen.hpp"

int yura_popen::exec(const std::string& cmd) {

    std::cout << "コマンド：" << cmd << std::endl;
    std::system(cmd.c_str());
    return 1;
}


