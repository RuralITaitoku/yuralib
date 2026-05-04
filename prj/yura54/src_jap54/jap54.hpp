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
    int get_char_bytes(unsigned char first_byte); 
}; 
