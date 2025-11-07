#pragma once
#include "jap.hpp"
#include "yura.hpp"


class ivvi : public jap {
private:
    int left_row_;
    int left_col_;
    int right_row_;
    int right_col_;
    int row_;
    int col_;
    int width_;
    int height_;
    int center_col_;
    yuraterm term_;
    std::vector<std::string> left_buffer;
    std::vector<std::string> right_buffer;
    std::string top_line_;
    std::string bottom_line_;
public:
    ivvi();
    ~ivvi();
    virtual std::string help();
    virtual bool run(std::string &cmd, std::vector<std::string>& stack);

    int height();
    int width();

    int center_col();
    int row();
    int col();
    int lrow();
    int lcol();
    int rrow();
    int rcol();

    void set_left(int r, int c);
    void set_right(int r, int c);

    int print(const std::string &str, int fg, int bg);
};