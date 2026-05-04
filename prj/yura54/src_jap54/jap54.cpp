#include "jap54.hpp"


int jap54::get_utf8_byte_size(const std::string& str, size_t start_byte, int utf8_size) {
    if (start_byte < 0 || start_byte >= str.length()) {
        throw std::out_of_range("開始バイト位置が文字列の範囲外です。");
    }
    if (utf8_size <= 0) {
        throw std::invalid_argument("UTF8の文字数は正の数である必要があります。");
    }

    size_t current_byte = start_byte;
    int processed_chars = 0;

    while (processed_chars < utf8_size && current_byte < str.length()) {
        unsigned char first_byte = static_cast<unsigned char>(str[current_byte]);
        int char_bytes;

        if ((first_byte & 0x80) == 0) { // 0xxxxxxx (1 byte)
            char_bytes = 1;
        } else if ((first_byte & 0xE0) == 0xC0) { // 110xxxxx (2 bytes)
            char_bytes = 2;
        } else if ((first_byte & 0xF0) == 0xE0) { // 1110xxxx (3 bytes)
            char_bytes = 3;
        } else if ((first_byte & 0xF8) == 0xF0) { // 11110xxx (4 bytes)
            char_bytes = 4;
        } else if ((first_byte & 0xFC) == 0xF8) { // 111110xx (5 bytes)
            char_bytes = 5;
        } else {
            // 不正なUTF-8シーケンス
            throw std::invalid_argument("不正なUTF-8シーケンスが文字列に含まれています。");
        }

        if (current_byte + char_bytes > str.length()) {
            // 文字列の終わりを超えた
            throw std::out_of_range("指定されたUTF8文字数に対応するバイト数が文字列の範囲外です。");
        }

        current_byte += char_bytes;
        processed_chars++;
    }
    return current_byte - start_byte;
}

#ifdef ENABLE_TEST
TEST(TestJap54, get_utf8_byte_size_ut00) {
    // int jap54::get_utf8_byte_size(const std::string& str, size_t start_byte, int utf8_size)
    // test1
    auto test_size = jap54::get_utf8_byte_size("テスト");
    EXPECT_EQ(test_size, 9);
    // test2 
    test_size = jap54::get_utf8_byte_size("テaス0ト");
    EXPECT_EQ(test_size, 11);
    // test3 
    test_size = jap54::get_utf8_byte_size("Ā");
    EXPECT_EQ(test_size, 2);
}
#endif


int jap54::get_char_bytes(unsigned char first_byte) {
    int char_bytes;
    if ((first_byte & 0x80) == 0) { // 0xxxxxxx (1 byte)
        char_bytes = 1;
    } else if ((first_byte & 0xE0) == 0xC0) { // 110xxxxx (2 bytes)
        char_bytes = 2;
    } else if ((first_byte & 0xF0) == 0xE0) { // 1110xxxx (3 bytes)
        char_bytes = 3;
    } else if ((first_byte & 0xF8) == 0xF0) { // 11110xxx (4 bytes)
        char_bytes = 4;
    } else if ((first_byte & 0xFC) == 0xF8) { // 111110xx (5 bytes)
        char_bytes = 5;
    } else {
        // 不正なUTF-8シーケンス
        throw std::invalid_argument("不正なUTF-8シーケンスが文字列に含まれています。");
    }
    return char_bytes;
}

#ifdef ENABLE_TEST
TEST(TestJap54, get_char_bytes) {
    // int jap54::get_char_bytes(unsigned char first_byte) {
    // test1
    std::string test_str = "あ";
    auto test_size = jap54::get_char_bytes(test_str[0]);
    EXPECT_EQ(test_size, 3);
    // test2
    test_str = "aaa";
    test_size = jap54::get_char_bytes(test_str[0]);
    EXPECT_EQ(test_size, 1);
}
#endif


