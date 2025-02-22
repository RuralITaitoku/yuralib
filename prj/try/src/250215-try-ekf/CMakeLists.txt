cmake_minimum_required(VERSION 3.10)
project(EKFProject)

# set(CMAKE_CXX_STANDARD 11)

# テストの設定を有効化
enable_testing()



find_package(Curses REQUIRED)

set(SRC_FILES try-ekf.cpp)


add_executable(try-ekf ${SRC_FILES})
target_link_libraries(try-ekf  gtest_main ${CURSES_LIBRARIES})
# テストを登録
add_test(NAME try-ekf COMMAND try-ekf)