#include "jap0.hpp"


jap0_sqlite::jap0_sqlite() {}

jap0_sqlite::~jap0_sqlite() {}


void jap0_sqlite::help() {
    std::cout << "jap0_sqlite_help" << std::endl;
}

bool jap0_sqlite::run(const std::string& cmd, std::vector<std::string>& stack) {
    if (cmd == "br_test") {
        std::cout << "bit reverse test" << std::endl;
        return true;
    }
    return false;

}

int jap0_sqlite::bit_reverse4(int s) {
    return ((s & 8) >> 3) | ((s & 4) >> 1) | ((s & 2) << 1) | ((s & 1) << 3); 
}