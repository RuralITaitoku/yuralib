cmake_minimum_required(VERSION 3.10)
project(TryProject)

# set(CMAKE_CXX_STANDARD 11)
# Google TestをFetchContentでダウンロード
cmake_policy(SET CMP0135 NEW)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  )
# ダウンロードしたgtestを使用可能にする
FetchContent_MakeAvailable(googletest)





if(EXISTS "/opt/homebrew")
    message(STATUS "Homebrew is installed.")
    # Homebrewがインストールされている場合の処理
    include_directories(/opt/homebrew/include/eigen3)
else()
    message(STATUS "Homebrew is not installed.")
    # Homebrewがインストールされていない場合の処理
    include_directories(/usr/include/eigen3)
endif()
include_directories(${PROJECT_SOURCE_DIR}/include)  

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
add_subdirectory(250125-try-utf8)
# add_subdirectory(250201-try-sdl)
add_subdirectory(250202-try-dijkstra)
add_subdirectory(250215-try-ekf)
