#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

class task {
public:
    int next_millis = 0;
    virtual ~task() {
        std::cout << "taskデストラクタ" << std::endl;
    };

    int millis() {
        // システムクロックを取得
        auto now = std::chrono::system_clock::now();
        // time_point を duration に変換 (秒単位)
        auto duration = now.time_since_epoch();
        // duration をミリ秒に変換
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
        return static_cast<int>(milliseconds.count());
    }
    virtual void setup() = 0;
    virtual int loop() = 0;
};

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
        std::cout << "ニャーニ " << millis() << std::endl;
        return 2000;
    }
};

#define DP(x) std::cout << __FILE__ << ":" << __LINE__ <<  " " << (x) << std::endl;

class task_mng : public task {
public:
    std::vector<task*> task_lists;

    void add_task(task& t) {
        task_lists.push_back(&t);
    }

    void setup() override {
    }
    int loop() override {
        std::cout << "task_mng loop" << std::endl;
        for (;;) {
            int now = millis();
            for (task* t: task_lists) {
                int next = t->next_millis;
                if (next < 0 || next > now) {
                    continue;
                }
                next = t->loop();
                if (next < 0) {
                    t->next_millis = -1;
                    continue;    
                }
                t->next_millis = now + next;
            }
            int min_next = now + (24 * 60 * 60 * 1000);
            for (task* t: task_lists) {
                int next = t->next_millis;
                if (next < -1) {
                    continue;
                }
                if (next < min_next) {
                    min_next = next;
                }
            }
            if ((min_next - now) > 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(min_next - now));
            }
        }


        return 0;
    }
};



int main() {

    task_mng mng;

    Dog dog;
    Cat cat;
    
    mng.add_task(dog);
    mng.add_task(cat);

    mng.setup();
    mng.loop();


    return 0;
}

