#include <task.hpp>


int64_t task::my_epoch = 0;

task::~task(){}

int task::millis() {
    // システムクロックを取得
    auto now = std::chrono::system_clock::now();
    // time_point を duration に変換 (秒単位)
    auto duration = now.time_since_epoch();
    // duration をミリ秒に変換
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    if (my_epoch == 0) {
        my_epoch = milliseconds.count();
    }
    return static_cast<int>(milliseconds.count() - my_epoch);
}

void task_mng::add_task(task& t) {
    task_lists.push_back(&t);
}

void task_mng::setup() {
}

int task_mng::loop() {
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
