#pragma once
#include <iostream>
#include <vector>

class jap {
public:
    virtual std::string help() = 0;
    virtual bool run(std::string &cmd, std::vector<std::string>& stack) = 0;

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



};
