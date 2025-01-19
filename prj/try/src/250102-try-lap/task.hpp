
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

class task {
public:
    int next_millis;
    std::string name;

    int millis() {
        // システムクロックを取得
        auto now = std::chrono::system_clock::now();
        // time_point を duration に変換 (秒単位)
        auto duration = now.time_since_epoch();
        // duration をミリ秒に変換
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
        return static_cast<int>(milliseconds.count());
    }
    virtual void setup() {
        next_millis = millis() + 1000;
        std::cout << "setup" << next_millis << std::endl;
    }

    virtual int loop() {
        std::cout << name << ":loop" << std::endl;
        return 1000;
    }
};



class task_mng : public task {
public: 
    int max_wait = 12 * 60 * 60 * 1000;
    std::vector<task> task_lists;
    
    void  add_task(task& task) {
        task_lists.push_back(task);
    }

    virtual void setup() {
        for (task& t: task_lists) {
            t.setup();
        }
    }

    virtual int loop() {
        std::cout << "mng loop" << std::endl;

        for (;;) {
            int now = millis();
            int min_next = now + max_wait;
            for (task& t: task_lists) {
                int next = t.next_millis;
                if (0 < next) {
                    if (next <= now){
                        next = t.loop();
                        if (next < 0) {
                            t.next_millis = -1;
                            next = now + max_wait;
                        } else if (next == 0) {
                            next = now;
                            t.next_millis = 0;
                        } else {
                            next += now;
                            t.next_millis = next;
                        }
                    }
                    if (next < min_next) {
                        min_next = next;
                    }
                }
            }
            if (min_next < now) {
                std::cout << "min_next=" << min_next << std::endl;
                std::cout << "now     =" << now << std::endl;
                std::cout << "min_next < now!!!!!" << std::endl;
                min_next = now;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(min_next - now));
        }

        return 0;
    }
};
