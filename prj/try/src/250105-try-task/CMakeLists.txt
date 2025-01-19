cmake_minimum_required(VERSION 3.10)
project(MyProject)

# set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

set(SRC_FILES try-task.cpp)
add_executable(try-task ${SRC_FILES})

target_link_libraries(try-task ${OpenCV_LIBS})
include_directories(/opt/homebrew/include/eigen3)
