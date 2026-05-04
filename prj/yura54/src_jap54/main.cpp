#include <gtest/gtest.h>
#include "jap54.hpp"

int tests(int argc, char **argv) {
    // 1. Google Testの初期化（コマンドライン引数の解析など）
    printf("Running main() from custom_main.cpp\n");
    testing::InitGoogleTest(&argc, argv);

    // 2. 必要に応じてここで独自の設定（グローバルなセットアップなど）を行う

    // 3. すべてのテストを実行
    // RUN_ALL_TESTS() は成功時に0、失敗時に1を返します
    return RUN_ALL_TESTS();
}

int main(int argc, char **argv) {
    std::vector<std::string> args;
    for (int i = 0; i < argc;i++) {
        args.push_back(argv[i]);
        std::cout << i << ":" << args.back() << std::endl;
    }
    return tests(argc, argv);
}
/*
#include <iostream>
#include "async_get_char.hpp"

int main(int argc, char** argv) {
    std::cout << "jap54 !" << std::endl;
}
int main1(int argc, char **argv) {
    jap_async async;

    std::string ch;
    for (;;) {
       async.getChar(0, ch, 1999999, true); 
    }
}
*/
