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
