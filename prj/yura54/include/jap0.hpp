#pragma once

#include "jap.hpp"
#include <regex>
#include <cstdio>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

class jap0 : public jap {
public:
    virtual void help() override;
    virtual bool run(const std::string &cmd, std::vector<std::string>& stack) override;

    bool check_line(const std::string& text, std::string& prefix, int& no, std::string& line);
    bool check_pattern(const std::string& text, const std::regex& pattern, std::vector<std::string>& result);

private:
    std::regex line_pattern_ = std::regex(R"(^([0-9]*)\. (.*)$)");
};

#define ERASE_TO_END_OF_LINE "\x1b[K";

class jap0_screen {
    std::vector<uint64_t> screen_;
    std::vector<uint64_t> off_screen_;
    int width_;
    int height_;
    int cur_x_;
    int cur_y_;
    void int64_to_char_big_endian(int64_t value, char buffer[8]) {
        for (int i = 0; i < 8; ++i) {
            // (7 - i) は 7, 6, 5, ..., 0 の順でシフト量を計算
            // value を右にシフトし、最下位バイト (0xFF) とのビットANDを取る
            buffer[i] = (char)((value >> ((7 - i) * 8)) & 0xFF);
        }
    }
public:
    jap0_screen() {};
    ~jap0_screen() {};

    void init(int width, int heigth);
    void put(int x, int y, char ch);
    void drawLine(int x0, int y0, int x1, int y1, char ch);
    void println(const std::string& line, int x = 0, int y = 0);
    void input(std::string& line);
    void flush(int x, int y);
};

class jap0_term {
    jap0_screen lscreen_;
    jap0_screen rscreen_;
    struct termios old_termios;
    int rows_;
    int cols_;
public:
    jap0_term();
    ~jap0_term();

    void get_line(std::string& line);
    void println(std::string& line, int row=0, int col=0);
    std::tuple<int, int> get_term_size();
    std::string es_cursor(int row, int col);
    std::string es_end();
};


