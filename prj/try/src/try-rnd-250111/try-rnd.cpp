#include <iostream>


#include "rng.hpp"


int main() {
    // シードを設定して初期化
    LinearCongruentialGenerator rng(12345);

    // ランダムな値を生成
    for (int i = 0; i < 10; ++i) {
        std::cout << rng.next(1, 10000) << std::endl; // 1～100の範囲
    }

    return 0;
}
