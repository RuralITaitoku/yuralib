
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

#ifndef __TASK__
#define __TASK__

class task {
public:
    static int64_t my_epoch;
    int next_millis = 0;
    virtual ~task();

    int millis();
    virtual void setup() {};
    virtual int loop() = 0;
};

class task_mng : public task {
public:
    std::vector<task*> task_lists;

    void add_task(task& t);
    void setup() override;
    int loop() override;
};


#endif