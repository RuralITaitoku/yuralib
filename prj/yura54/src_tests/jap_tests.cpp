#include <gtest/gtest.h>

TEST(Test, hello) {
	FAIL()<< "test";
}



int main(int argc, char **argv) {
    // 1. Google Testの初期化（コマンドライン引数の解析など）
    printf("Running main() from custom_main.cpp\n");
    testing::InitGoogleTest(&argc, argv);

    // 2. 必要に応じてここで独自の設定（グローバルなセットアップなど）を行う

    // 3. すべてのテストを実行
    // RUN_ALL_TESTS() は成功時に0、失敗時に1を返します
    return RUN_ALL_TESTS();
}

