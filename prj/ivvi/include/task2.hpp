
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

#ifndef __TASK__
#define __TASK__

class task {
public:
    double next_millis = 0;
    virtual ~task() {
        std::cout << "taskデストラクタ" << std::endl;
    };

    double millis() {
        // システムクロックを取得
        auto now = std::chrono::system_clock::now();
        // time_point を duration に変換 (秒単位)
        auto duration = now.time_since_epoch();
        // duration をミリ秒に変換
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
        return static_cast<double>(milliseconds.count());
    }
    virtual void setup() {};
    virtual double loop() = 0;
};


class task_mng : public task {
public:
    std::vector<task*> task_lists;

    void add_task(task& t) {
        task_lists.push_back(&t);
    }

    void setup() override {
        for (task* t: task_lists) {
            t->setup();
        }
    }
    double loop() override {
        std::cout << "task_mng loop" << std::endl;
        for (;;) {
            double now = millis();
            for (task* t: task_lists) {
                double next = t->next_millis;
                if (next < 0 || now < next) {
                    continue;
                }
                next = t->loop();
                if (0 < next) {
                    t->next_millis = now + next;
                }
            }
            uint64_t min_next = now + (24 * 60 * 60 * 1000);
            std::cout << __LINE__ << "_"<< (min_next - now) <<std::endl;
            for (task* t: task_lists) {
                uint64_t next = t->next_millis;
                if (next < -1) {
                    continue;
                }
                if (next < min_next) {
                    min_next = next;
                }
            }
            std::cout << __LINE__ << "min_next = " << min_next << ", now = " << now << "c"<< (min_next - now) <<std::endl;
            if ((min_next - now) > 0) {
                int i = min_next - now;
                std::this_thread::sleep_for(std::chrono::milliseconds(i));
            }
            std::cout << __LINE__ << std::endl;
        }
        return 0;
    }
};


#endif              