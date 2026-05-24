#pragma once
#ifdef ENABLE_TEST
#include <gtest/gtest.h>
#endif 

#include <iostream>
#include <climits>

namespace jap54 {

    /**
     * @brief UTF8文字列を指定位置の指定文字数でのバイト数を取得する。
     * @param str 文字列
     * @param start_byte 指定位置をバイト数で指定。
     * @param utf8_size 文字数
     * @return バイト数
     */
    int get_utf8_byte_size(const std::string& str, size_t start_byte = 0, int utf8_size = INT_MAX);
    
    /**
     * @brief UTF8の先頭バイトから、文字のバイト数を取得する。 
     * @param first_byte 先頭バイト 
     * @return バイト数
     */
    inline int get_char_bytes(unsigned char first_byte) {
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
            throw std::invalid_argument("The string contains an invalid UTF-8 sequence.");
        }
        return char_bytes;
    }
    /**
     * @brief UTF8文字列を指定位置の指定文字数でのターミナル上の幅を取得する。
     * @param str 文字列
     * @param start_byte 指定位置をバイト数で指定。
     * @param utf8_size 文字数
     * @return ターミナル上の幅
     */
    int get_utf8_term_width(const std::string& str, size_t start_byte = 0, int utf8_size = INT_MAX);

    /**
     * @brief UTF8文字列を指定位置の指定文字数での画面上の幅を取得する。
     * @param str 文字列
     * @param start_byte 指定位置をバイト数で指定。
     * @param utf8_size 文字数
     * @return 画面上の幅
     */
    uint32_t hash32(const void* data, size_t size);
 }; 
