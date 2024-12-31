cmake_minimum_required(VERSION 3.10)
project(MyProject)

# set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

set(SRC_FILES test.cpp)
add_executable(test ${SRC_FILES})

target_link_libraries(test ${OpenCV_LIBS})
include_directories(/opt/homebrew/include/eigen3)
# find_package(Eigen3 REQUIRED  VERSION 3.4)
#find_package(Eigen3 REQUIRED  VERSION 3.4)
#target_link_libraries(my_executable Eigen::Eigen)