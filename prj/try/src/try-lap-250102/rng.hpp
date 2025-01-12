class LinearCongruentialGenerator {
private:
    unsigned long seed;  // 現在の値（シード）
    const unsigned long a = 1664525; // 乗数
    const unsigned long c = 1013904223; // 加算定数
    const unsigned long m = 4294967296; // モジュラス (2^32)

public:
    // コンストラクタ
    LinearCongruentialGenerator(unsigned long initial_seed) : seed(initial_seed) {}

    // 次の乱数を生成
    unsigned long next() {
        seed = (a * seed + c) % m;
        return seed;
    }

    // 任意の範囲で乱数を生成 (minからmaxまで)
    long next(long min, long max) {
        return min + (next() % (max - min + 1));
    }
};


