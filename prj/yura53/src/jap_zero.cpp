#include "jap_zero.hpp"
#include "yura.hpp"

template<typename T> class TypeCheck;
#define DP(x) std::cout << __FILE__ << ":" << __LINE__ << " " << x << std::endl;

bool jap_zero::run(std::string &cmd, std::vector<std::string> &stack) {
    if (cmd == "jap0" || cmd == "jf") {
    }
    return false;
}
void jap_zero::main() {
    std::cout << "jap0 main" << std::endl;
    std::string line;
    std::vector<std::string> stack;
    for(;;) {
        getline(std::cin, line);
        std::cout << line << std::endl;

    }

}