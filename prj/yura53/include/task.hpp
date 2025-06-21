#pragma once


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <thread>


class task {
public:
    static int64_t my_epoch;
    int next_millis = 0;
    virtual ~task();

    int millis();
    void set_next(int m);
    virtual void setup() {};
    virtual int loop(std::map<std::string, std::string>& circle) = 0;
};

class task_mng : public task {
public:
    std::vector<task*> task_lists;

    void add_task(task& t);
    void setup() override;
    int loop(std::map<std::string, std::string>& circle) override;
};
