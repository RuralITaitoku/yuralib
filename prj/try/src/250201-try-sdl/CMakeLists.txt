cmake_minimum_required(VERSION 3.10)
project(TrySDLProject)

# set(CMAKE_CXX_STANDARD 11)
find_package(SDL3 REQUIRED)

set(SRC_FILES try-sdl.cpp)
add_executable(try-sdl ${SRC_FILES})
target_link_libraries(try-sdl SDL3::SDL3)
