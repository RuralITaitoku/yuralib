#include <gtest/gtest.h>

#include "utf8lines.hpp"








TEST(Utf8LinesTest, DisplayTest) {
    utf8lines lines;


    lines.debug_print();

    std::cout << "test" << std::endl;
}
