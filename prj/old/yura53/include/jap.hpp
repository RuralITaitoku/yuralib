#pragma once
#include <chrono>
#include <iostream>
#include <vector>
#include <memory>

class jap {
public:
    virtual ~jap() {};
    virtual void help() = 0;
    virtual bool run(const std::string &cmd, std::vector<std::string>& stack) = 0;

    int next_millis;

    int millis() {
        static uint64_t jap_epoch = 0;
        // システムクロックを取得
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        // duration をミリ秒に変換
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
        if (jap_epoch == 0) {
            jap_epoch = milliseconds;
        }
        return static_cast<int>(milliseconds - jap_epoch);
    }

    int next() {
        return next_millis;
    }

    void set_next(int n) {
        next_millis = millis() + n;
    }



};
