#include <gtest/gtest.h>

#include "utf8lines.hpp"

/*
* @breif Values ​​are assigned correctly using operator=
*/
TEST(Utf8LinesTest, AssignmentOperator_DifferentValues) {
    utf8lines line;
    std::string ans = "test";
    line = "test";
 
    EXPECT_EQ(line, "test");
}

TEST(Utf8LinesTest, test02) {
    utf8lines line;
    std::string ans = "test";
    line.put(2, "test");
    line.put(4, "test");
    line.print();
    EXPECT_EQ(line, "  tetest");
}


