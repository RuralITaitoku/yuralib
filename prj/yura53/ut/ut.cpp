#include "gtest/gtest.h"

int main(int argc, char **argv) {
  // GTestフレームワークを初期化し、コマンドライン引数を処理します。
  ::testing::InitGoogleTest(&argc, argv); 
  
  // 登録されている全てのテストを実行します。
  // テストが全て成功した場合、この関数は0を返します。
  return RUN_ALL_TESTS();
}

TEST(aaa, bbb) {

    EXPECT_TRUE(false);
}