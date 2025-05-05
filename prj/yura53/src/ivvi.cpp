#include "ivvi.hpp"
#include "task.hpp"
#include <iostream>


ivvi::ivvi() {
    std::cout << "ivvi constructor" << std::endl;
}

ivvi::~ivvi() {
    std::cout << "ivvi distructor" << std::endl;
}

void ivvi::setup() {

}
int ivvi::loop(std::map<std::string, std::string>& circle) {
    std::cout << "ivvi loop" << std::endl;
    return 1000;
}
