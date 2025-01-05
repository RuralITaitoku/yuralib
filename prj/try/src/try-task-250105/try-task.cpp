#include "task.hpp"


class Dog : public task {
public:
    void setup() override {
    }
    int loop() override {
        std::cout << "ワンワン " << millis() << std::endl;
        return 1000;
    }
};

class Cat : public task {
public:
    void setup() override {
    }
    int loop() override {
        std::cout << "ニャーニャー " << millis() << std::endl;
        return 3300;
    }
};

#define DP(x) std::cout << __FILE__ << ":" << __LINE__ <<  " " << (x) << std::endl;


class screen_task : public task {
public:

    int loop() override {

        DP("screen task");
        return 9000;
    }



};


int main() {

    task_mng mng;

    Dog dog;
    Cat cat;
    screen_task screen;
    mng.add_task(dog);
    mng.add_task(cat);
    mng.add_task(screen);

    mng.setup();
    mng.loop();


    return 0;
}

