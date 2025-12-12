#include "jap0.hpp"




std::string jap0::help() {
    std::string result;
    result += "jap0::help!!!!!!!!!!!!!!!!";
    return result;
}
bool jap0::run(const std::string& cmd, std::vector<std::string>& stack) {
    if (cmd == "jap0") {
        std::cout << "jap0 test" << std::endl;
        return true;
    }
    return false;
}


