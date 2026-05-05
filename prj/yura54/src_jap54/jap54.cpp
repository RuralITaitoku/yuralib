#include "jap54.hpp"


int jap54::get_utf8_byte_size(const std::string& str, size_t start_byte, int utf8_size) {
    if (start_byte < 0 || start_byte >= str.length()) {
        throw std::out_of_range("The startting byte postion is outside the range of the string.");
    }
    if (utf8_size <= 0) {
        throw std::invalid_argument("The number of characters in a UTF-8 encoding must be a positive number.");
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
        } else {
            // 不正なUTF-8シーケンス
            throw std::invalid_argument("The string contains an invalid UTF-8 sequence.");
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
    // test4 
    test_size = jap54::get_utf8_byte_size("𐄢");
    EXPECT_EQ(test_size, 4);
}
TEST(TestJap54, get_utf8_byte_size_ut01) {
    // int jap54::get_utf8_byte_size(const std::string& str, size_t start_byte, int utf8_size)
    // test1
    try {
        jap54::get_utf8_byte_size("テスト", -1);
        FAIL() << "The expected exception did not occur.";
    } catch (const std::out_of_range &e) {
        EXPECT_STREQ(e.what(), "The startting byte postion is outside the range of the string.");
    } catch (...) {
        FAIL() << "Unexpected exception error."; 
    }
}
TEST(TestJap54, get_utf8_byte_size_ut02) {
    // int jap54::get_utf8_byte_size(const std::string& str, size_t start_byte, int utf8_size)
    // test1
    try {
        jap54::get_utf8_byte_size("テスト", 0, -1);
        FAIL() << "The expected exception did not occur.";
    } catch (const std::invalid_argument &e) {
        EXPECT_STREQ(e.what(), "The number of characters in a UTF-8 encoding must be a positive number.");
    } catch (...) {
        FAIL() << "Unexpected exception error."; 
    }
}
TEST(TestJap54, get_utf8_byte_size_ut03) {
    // int jap54::get_utf8_byte_size(const std::string& str, size_t start_byte, int utf8_size)
    try {
        std::string test_str = "aaaa";
        test_str[0] = (unsigned char)0xff;
        jap54::get_utf8_byte_size(test_str);
        FAIL() << "The expected exception did not occur.";
    } catch (const std::invalid_argument &e) {
        EXPECT_STREQ(e.what(), "The string contains an invalid UTF-8 sequence.");
    } catch (...) {
        FAIL() << "Unexpected exception error."; 
    }
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
    } else {
        // 不正なUTF-8シーケンス
        throw std::invalid_argument("The string contains an invalid UTF-8 sequence.");
    }
    return char_bytes;
}

#ifdef ENABLE_TEST
TEST(TestJap54, get_char_bytes_ut_00) {
    // int jap54::get_char_bytes(unsigned char first_byte) {
    // test1
    std::string test_str = "あ";
    auto test_size = jap54::get_char_bytes(test_str[0]);
    EXPECT_EQ(test_size, 3);
    // test2
    test_str = "aaa";
    test_size = jap54::get_char_bytes(test_str[0]);
    EXPECT_EQ(test_size, 1);
    // test3
    test_str = "Ā";
    test_size = jap54::get_char_bytes(test_str[0]);
    EXPECT_EQ(test_size, 2);
    // test4 
    test_str = "𐄢";
    test_size = jap54::get_char_bytes(test_str[0]);
    EXPECT_EQ(test_size, 4);
}
TEST(TestJap54, get_char_bytes_ut_01) {
    // int jap54::get_char_bytes(unsigned char first_byte) {
    try {
        std::string test_str = "aaaa";
        test_str[0] = (unsigned char)0xff;
        jap54::get_char_bytes(test_str[0]);
        FAIL() << "The expected exception did not occur.";
    } catch (const std::invalid_argument &e) {
        EXPECT_STREQ(e.what(), "The string contains an invalid UTF-8 sequence.");
    } catch (...) {
        FAIL() << "Unexpected exception error."; 
    }
}
#endif


