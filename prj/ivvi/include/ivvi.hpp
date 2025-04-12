#include "yuraterm.hpp"
#include "task.hpp"

#pragma once
#define jc
class ivvi_screen : public task {

public:
    yuraterm yura;
    int cursor_row;
    int cursor_col;
    int width;
    int height;
    bool screen_update;
    std::vector<uint64_t> data;

    void cursor(int r, int c);
    void setup() override;
    int loop(std::map<std::string, std::string>& circle) override;
    void validate();

    std::string get_utf8(std::string& utf8, int index);
    std::string get_string(uint64_t utf8, bool little_endian = false);
    int next_utf8(std::string& utf8, int index);
    uint64_t get_int64(std::string& utf8);

    void put(int x, int y, uint64_t ch);
    void draw_line(int x1, int y1, int x2, int y2, uint64_t ch);
    void draw_string(int x, int y, std::string str);
    std::string get(uint64_t ch);
};



class ivvi : public task {
    int lr = 0;
    int lc = 0;
public:
    ivvi_screen screen;
    void setup() override;
    int loop(std::map<std::string, std::string>& circle) override;
};




