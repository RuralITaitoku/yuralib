cmake_minimum_required(VERSION 3.10)
project(TryProject)

# set(CMAKE_CXX_STANDARD 11)

# テストの設定を有効化
enable_testing()



set(SRC_FILES utf8lines.cpp)


add_executable(try-utf8lines ${SRC_FILES})
target_link_libraries(try-utf8lines  gtest gtest_main)
# テストを登録
add_test(NAME try-utf8lines COMMAND try-utf8lines)