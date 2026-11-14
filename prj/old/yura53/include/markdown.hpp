#pragma once
#include <sstream>
#include <string>
#include <vector>
#include "yura.hpp"

class markdown {
public:
    enum ErrorCode {
        OK = 0,
        NG = 1
    };
    int line_render(const std::string& line, std::string& html);
    int render(const std::string& md, std::string& html, std::string& toc_html);
    std::string html(const std::string& md);

};