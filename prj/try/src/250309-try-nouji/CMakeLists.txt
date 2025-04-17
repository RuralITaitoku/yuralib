cmake_minimum_required(VERSION 3.10)
project(TryNouji)


file(GLOB SRC_FILES "*.cpp")
#set(SRC_FILES try-nouji.cpp)
add_executable(try-nouji ${SRC_FILES})

