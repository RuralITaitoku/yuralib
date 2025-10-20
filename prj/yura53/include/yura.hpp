#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <ctime>
#include "yura_pipe.hpp"
#include "yuraterm.hpp"

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

    /**
     * @brief テキストをcsvデータに変換する。
     * @param text テキスト
     * @return csv
     */
    std::vector<std::vector<std::string>> to_csv(std::string &text);
    std::string to_csv_text(std::vector<std::vector<std::string>> &csv);

    /**
     * @brief 現在の日付をYYYYMMDD形式の整数で取得します。
     * @details システムの現在時刻を取得し、ローカルタイムに変換した後、
     *          年、月、日の各要素を抽出し、`YYYY * 10000 + MM * 100 + DD`の形式の
     *          整数に変換して返します。
     *          **注意:** このメソッドは内部で`std::localtime`を使用しており、スレッドセーフではありません。
     * @return 現在の日付を表すYYYYMMDD形式の整数。
     */
    int today();
    /**
     * @brief YYYYMMDD形式の整数で表された日付に、指定した日数を加算します。
     * @details 内部で`std::mktime`を使用することで、月の繰り上がりや年の繰り上がりを
     *          自動で処理し、正確な日付計算を行います。
     *          **注意**: このメソッドはローカルタイムを基準に動作するため、
     *          夏時間（Daylight Saving Time）の影響を受ける可能性があります。
     * @param base YYYYMMDD形式の整数で表された基準日。
     * @param days_to_add 加算する日数（負の数を指定することで減算も可能）。
     * @return 日数が加算された後の日付をYYYYMMDD形式の整数で返します。
     *         日付の変換に失敗した場合の戻り値は未定義です。
     */
    int add_days(int base, int days);

    /**
     * @brief 現在のUTC時刻をYYYYMMDDHHMMSSmmm形式のuint64_tで取得します。
     * @details C++11の`std::chrono::system_clock`と`<ctime>`を利用して、
     *          高精度なミリ秒単位の時刻を取得し、指定された形式に変換します。
     * @return 変換された時刻を表すuint64_t値。
     */
    uint64_t get_current_time_uint64_t();

    /**
     * @brief YYYYMMDDHHMMSSmmm形式のuint64_tからstd::tm構造体とミリ秒を取得します。
     * @param timestamp YYYYMMDDHHMMSSmmm形式のuint64_t値。
     * @param tm 変換結果を格納するstd::tm構造体への参照。
     * @param milliseconds 変換結果を格納するミリ秒への参照。
     * @return 変換に成功した場合はtrue、無効な形式の場合はfalse。
     */
    bool from_uint64_t_to_tm(uint64_t timestamp, std::tm& tm, int& milliseconds);

    /**
     * @brief YYYYMMDDHHMMSSmmm形式のuint64_tのstartとendの差をミリ秒で求めます。
     * @param start 開始時刻（uint64_t）。
     * @param end 終了時刻（uint64_t）。
     * @return startとendの差のミリ秒。start > endの場合は負の値になります。
     * @throw std::invalid_argument 無効なタイムスタンプが入力された場合にスローされます。
     */
    int64_t diff_milli_secound(uint64_t start, uint64_t end);



    int exec(std::string& cmd);
    bool is_all_whitespace(const std::string& str) ;
    int get_char_bytes(unsigned char first_byte);
};
