#include "gtest/gtest.h"
#include "ivvi.hpp"
int main(int argc, char **argv) {
  // GTestフレームワークを初期化し、コマンドライン引数を処理します。
  ::testing::InitGoogleTest(&argc, argv); 
  
  // 登録されている全てのテストを実行します。
  // テストが全て成功した場合、この関数は0を返します。
  return RUN_ALL_TESTS();
}

TEST(ivvi, disp) {
  ivvi screen;
}