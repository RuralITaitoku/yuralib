#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#define DP(x) std::cout << __FILE__ << ":" << __LINE__ << " " << x << std::endl;
/**
 * - [ ] CSV形式ファイルの読み書き
 */
namespace yura {
    /**
     * @brief テキストファイルを読み込む。
     * @param filename テキストファイル名
     * @return ファイルのテキスト
     */
    std::string load(const std::string& filename);

    /**
     * @brief テキストファイルを書き込む
     * @param filename テキストファイル名
     * @param text テキストファイル
     */
    void save(const std::string& filename, const std::string& text);

    /**
     * @brief 文字列の指定文字列を別の文字列に置換
     * @param str 元の文字列
     * @param from 置換対象文字列
     * @param to 置換文字列
     * @return 置換した文字列
     */
    std::string replace_all(std::string str, const std::string& from, const std::string& to);

    /**
     * @brief 文字列を指定文字で分割する
     * @param str 分割する文字列
     * @param term 区切り文字
     * @return 分割した文字列の配列
     */
    std::vector< std::string > split(const std::string& str, const std::string& term = "\n");

    /**
     * @brief 文字列の開始位置から指定UTF9の文字数までのバイト数を求める。
     * @param str 対象の文字列
     * @param start　開始バイト位置
     * @param utf8_size UTF8の文字数
     * @return バイト数
     */
    int get_utf8_byte_size(const std::string& str, size_t start_byte, int utf8_size = 1);

    /**
     * @brief 16進数表記の文字であるかの判定
     * @param c 判定する文字
     * @return true:16進表記の構成文字である。
     */
    bool is_hex_digit(char c);    
    std::string urldecode(const std::string& encoded_str);
    std::string urlencode(const std::string& str);
    std::string esc_html(const std::string& str);

    /**
     * @brief ファイルの存在チェック
     * @param filename ファイル名
     * @return true:ファイルが存在する。
     */
    bool fileExists(const std::string &filename) ;

    /**
     * @brief 左トリム (Leading whitespace)
     * @param s 対象文字列
     * @return トリムした文字列
     */
    std::string ltrim(const std::string& s);

    /**
     * @brief 右トリム (Trailing whitespace)
     * @param s 対象文字列
     * @return トリムした文字列
     */
    std::string rtrim(const std::string& s);

    /**
     * @brief トリム 
     * @param s 対象文字列
     * @return トリムした文字列
     */
    std::string trim(const std::string& s);

};
