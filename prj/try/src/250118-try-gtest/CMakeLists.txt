cmake_minimum_required(VERSION 3.10)
project(TryProject)

# set(CMAKE_CXX_STANDARD 11)

# テストの設定を有効化
enable_testing()



set(SRC_FILES try-gtest.cpp)
add_executable(try-gtest ${SRC_FILES})

target_link_libraries(try-gtest  gtest gtest_main)

# テストを登録
add_test(NAME try-gtest COMMAND try-gtest)