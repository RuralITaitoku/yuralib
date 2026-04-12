#include "jap1.hpp"

class jap1_main: public jap {
public:
    virtual ~jap1_main() {
    };

    virtual std::string help() {
        std::string help = "help";
    }



};

 
int main() {
    std::cout << "jap1 !" << std::endl; 
}
