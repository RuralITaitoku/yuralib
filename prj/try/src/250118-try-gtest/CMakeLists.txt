cmake_minimum_required(VERSION 3.10)
project(MyProject)

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

# テストの設定を有効化
enable_testing()



set(SRC_FILES try-gtest.cpp)
add_executable(try-gtest ${SRC_FILES})

target_link_libraries(try-gtest  gtest gtest_main)

# テストを登録
add_test(NAME try-gtest COMMAND try-gtest)