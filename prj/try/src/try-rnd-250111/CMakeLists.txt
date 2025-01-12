cmake_minimum_required(VERSION 3.10)
project(MyProject)

# set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

set(SRC_FILES
        try-rnd.cpp
     )
add_executable(try-rnd ${SRC_FILES})

target_link_libraries(try-rnd ${OpenCV_LIBS})
# include_directories(/opt/homebrew/include/eigen3)
