cmake_minimum_required(VERSION 3.10)
project(MyProject)

# set(CMAKE_CXX_STANDARD 11)

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

add_subdirectory(241215-try-cv)
add_subdirectory(250102-try-lap)
add_subdirectory(250105-try-task)
add_subdirectory(250111-try-rnd)
add_subdirectory(250118-try-gtest)