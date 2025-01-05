cmake_minimum_required(VERSION 3.10)
project(MyProject)

# set(CMAKE_CXX_STANDARD 11)

set(SRC_FILES try-eigen-241214.cpp)
add_executable(run ${SRC_FILES})

if(EXISTS "/opt/homebrew")
    message(STATUS "Homebrew is installed.")
    # Homebrewがインストールされている場合の処理
    include_directories(/opt/homebrew/include/eigen3)
else()
    message(STATUS "Homebrew is not installed.")
    # Homebrewがインストールされていない場合の処理
    include_directories(/usr/include/eigen3)
endif()

# find_package(Eigen3 REQUIRED  VERSION 3.4)
#find_package(Eigen3 REQUIRED  VERSION 3.4)
#target_link_libraries(my_executable Eigen::Eigen)



add_subdirectory(test)
#target_link_libraries(my_program module1::module1 module2::module2)

add_subdirectory(try-cv-241215)
add_subdirectory(try-lap-250102)
add_subdirectory(try-task-250105)