#include "yura.hpp"
#include <stdexcept>
#include <chrono>
#include <ctime>   // std::time_t, std::localtimeを使うため
#include <iomanip> // std::put_timeを使うため

//#include <cstdint>

/**
 * @brief テキストファイルを読み込む。
 * @param filename テキストファイル名
 * @return ファイルのテキスト
 */
std::string yura::load(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    } else {
        return "";
    }
}

/**
 * @brief テキストファイルを書き込む
 * @param filename テキストファイル名
 * @param text テキストファイル
 */
void yura::save(const std::string& filename, const std::string& text) {
    std::ofstream ofs(filename);
    if (ofs.is_open()) {
        ofs << text << std::endl;
        ofs.close();
    } else {
        std::cerr << "ファイルを開けませんでした: " << filename << std::endl;
    }
}

/**
 * @brief 文字列の指定文字列を別の文字列に置換
 * @param str 元の文字列
 * @param from 置換対象文字列
 * @param to 置換文字列
 * @return 置換した文字列
 */
std::string yura::replace_all(std::string str, const std::string& from, const std::string& to) {
    std::string::size_type pos = str.find(from);
    while (pos != std::string::npos) {
        str.replace(pos, from.length(), to);
        pos = str.find(from, pos + to.length());
    }
    return str;
}

/**
 * @brief 文字列を指定文字で分割する
 * @param str 分割する文字列
 * @param term 区切り文字
 * @return 分割した文字列の配列
 */
std::vector<std::string> yura::split(const std::string& str, const std::string& term) {
    std::vector<std::string> result;
    size_t pos = 0;
    size_t prev = 0;
    while ((pos = str.find(term, prev)) != std::string::npos) {
        result.push_back(str.substr(prev, pos - prev));
        prev = pos + term.length();
    }
    std::string word = str.substr(prev);
    if (!word.empty() && word.back() == '\r') {
        word.pop_back();
    }
    result.push_back(word);
    return result;
}

/**
 * @brief 文字列を指定位置の指定文字数でのバイト数を取得する。
 * @param str 文字列
 * @param start_byte 指定位置をバイト数で指定。
 * @param utf8_size 文字数
 * @return 分割した文字列の配列
 */
int yura::get_utf8_byte_size(const std::string& str, size_t start_byte, int utf8_size) {
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
int yura::get_char_bytes(unsigned char first_byte) {
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

// 左トリム (Leading whitespace)
std::string yura::ltrim(const std::string& s) {
    // std::find_if は、指定された範囲内で条件を満たす最初の要素を指すイテレータを返します。
    // ここでは、空白文字でない最初の文字を探します。
    size_t first = s.find_first_not_of(" \t\n\r\f\v"); // よく使われる空白文字を指定
    if (std::string::npos == first) { // 文字列がすべて空白の場合
        return "";
    }
    return s.substr(first); // 最初に見つかった空白でない文字以降を返します。
}

// 右トリム (Trailing whitespace)
std::string yura::rtrim(const std::string& s) {
    // std::find_last_not_of は、指定された文字セットに含まれない最後の文字を探します。
    // ここでは、空白文字でない最後の文字を探します。
    size_t last = s.find_last_not_of(" \t\n\r\f\v");
    if (std::string::npos == last) { // 文字列がすべて空白の場合
        return "";
    }
    // last + 1 は、最後の空白でない文字を含めて部分文字列を抽出するためです。
    return s.substr(0, last + 1);
}

// 左右トリム (Both leading and trailing whitespace)
std::string yura::trim(const std::string& s) {
    return ltrim(rtrim(s)); // まず右をトリムし、次に左をトリムします。
}


bool yura::is_hex_digit(char c) {
    return (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f') || (isdigit(c));
}
  
std::string yura::urldecode(const std::string& encoded_str) {
    std::string decoded_str;
  
    for (size_t i = 0; i < encoded_str.size(); ++i) {
      if (encoded_str[i] == '%') {
        if (i + 2 < encoded_str.size() && is_hex_digit(encoded_str[i + 1]) &&
            is_hex_digit(encoded_str[i + 2])) {
          // 16進数コードの場合
          char hex_char[3] = {encoded_str[i + 1], encoded_str[i + 2], '\0'};
          unsigned int code = std::stoul(hex_char, nullptr, 16);
          decoded_str += static_cast<char>(code);
          i += 2;
        } else {
          // エラー処理
          std::cerr << "Invalid URL encoding: " << encoded_str << std::endl;
          return "";
        }
      } else if (encoded_str[i] == '+') {
          decoded_str += ' ';
      } else {
          decoded_str += encoded_str[i];
  
      }
    }
  
    return decoded_str;
}
  
std::string yura::urlencode(const std::string& str) {
    std::string encoded_str;
  
    for (size_t i = 0; i < str.size(); i++) {
        unsigned char c = str[i];
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '*' ||
            c == ',' || c == ':' || c == '@' || c == '=' || c == '+' ||
            c == '$' || c == '(' || c == ')' || c == '[' || c == ']' ||
            c == '{' || c == '}' || c == ';' || c == '&' || c == '%' ||
            c == '<' || c == '>' || c == ',' || c == '?' || c == '/' ||
            c == '\\' || c == '^' || c == '`' || c == '|' || c == '~') {
            encoded_str += c;
        } else {
            encoded_str += "%";
            char hex_digits[3];
            snprintf(hex_digits, 3, "%02X", (int) c);
            hex_digits[2] = '\0';
            encoded_str.append(hex_digits, 2);
        }
    }
    return encoded_str;
}
  
std::string yura::esc_html(const std::string& str) {
    std::string esc_html;
    for (size_t i = 0; i < str.size(); i++) {
        unsigned char c = str[i];
        if (c == '<') {
            esc_html += "&lt;";
        } else if (c == '>') {
            esc_html += "&gt;";
        } else if ( c == '&') {
            esc_html += "&amp;";
        } else if ( c == '"') {
            esc_html += "&quot;";
        } else {
            esc_html += c;
        }
    }
    return esc_html;
}

bool yura::fileExists(const std::string &filename) {
    std::ifstream f(filename);
    return f.good();
}

int yura::today() {
    // 現在時刻のタイムスタンプを取得
    // std::chrono::system_clock::to_time_t を使うと、chrono::time_point を time_t に変換できます
    std::time_t now_c = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    // ローカルタイムに変換
    // 注意: std::localtime はスレッドセーフではない可能性があります。
    // マルチスレッド環境では localtime_r (Linux/macOS) や localtime_s (Windows) を検討してください。
    std::tm* local_time = std::localtime(&now_c);

    // 年月日を出力
    // tm_year は1900年からの年数、tm_mon は0から11、tm_mday は1から31
    std::cout << "Today's date: "
              << (local_time->tm_year + 1900) << "年"
              << (local_time->tm_mon + 1) << "月"
              << local_time->tm_mday << "日"
              << std::endl;
    int today = (local_time->tm_year + 1900) * 10000 + (local_time->tm_mon + 1) * 100 + local_time->tm_mday;
    return today;
}

int yura::weekday() {
    // 現在のシステム時刻（高分解能）を取得
    auto now = std::chrono::system_clock::now();
    
    // std::time_t型に変換
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    
    // UTC時刻に変換（スレッドセーフなgmtime_rを使用）
    std::tm time_info{};
#ifdef _WIN32
    gmtime_s(&time_info, &now_time_t); // Windows
#else
    gmtime_r(&now_time_t, &time_info); // POSIX
#endif

    return time_info.tm_wday;
    // 1:日曜日～7:日曜日
}

int yura::add_days(int base, int days_to_add) {
    int y = base / 10000;
    int m = (base / 100) % 100;
    int d = (base % 100);

    // 基準となる日付を設定
    std::tm t = {}; // ゼロ初期化
    t.tm_year = y - 1900; // 年は1900年からの経過年数
    t.tm_mon = m - 1;        // 月は0から11 (0=1月, 1=2月, ..., 11=12月)
    t.tm_mday = d;          // 日は1から31

    // mktime() を使って time_t に変換し、日付を正規化
    // この時点で mktime は tm_mday の値を調整し、月の終わりを越えても正しく処理します。
    std::mktime(&t);

    // 日数を加算
    t.tm_mday += days_to_add;

    // 再び mktime() を呼び出して日付を正規化
    // tm_mday が月の範囲を超えても、mktime が自動的に正しい月と年に調整してくれます。
    std::mktime(&t);

    int result = 0;

    return result;
}


/**
 * @brief 現在のUTC時刻をYYYYMMDDHHMMSSmmm形式のuint64_tで取得します。
 * @details C++11の`std::chrono::system_clock`と`<ctime>`を利用して、
 *          高精度なミリ秒単位の時刻を取得し、指定された形式に変換します。
 * @return 変換された時刻を表すuint64_t値。
 */
uint64_t yura::get_current_time_uint64_t() {
    // 現在のシステム時刻（高分解能）を取得
    auto now = std::chrono::system_clock::now();
    
    // 時刻をミリ秒単位に変換
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    
    // std::time_t型に変換
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    
    // UTC時刻に変換（スレッドセーフなgmtime_rを使用）
    std::tm time_info{};
#ifdef _WIN32
    gmtime_s(&time_info, &now_time_t); // Windows
#else
    gmtime_r(&now_time_t, &time_info); // POSIX
#endif

    // 各要素からuint64_tの数値を構築
    uint64_t result = 0;
    result += (uint64_t)(time_info.tm_year + 1900) * 10000000000000ULL; // YYYY
    result += (uint64_t)(time_info.tm_mon + 1) * 100000000000ULL;      // MM
    result += (uint64_t)time_info.tm_mday * 1000000000ULL;             // DD
    result += (uint64_t)time_info.tm_hour * 10000000ULL;               // HH
    result += (uint64_t)time_info.tm_min * 100000ULL;                  // MM
    result += (uint64_t)time_info.tm_sec * 1000ULL;                    // SS
    result += (uint64_t)milliseconds.count();                          // mmm

    return result;
}




/**
 * @brief YYYYMMDDHHMMSSmmm形式のuint64_tからstd::tm構造体とミリ秒を取得します。
 * @param timestamp YYYYMMDDHHMMSSmmm形式のuint64_t値。
 * @param tm 変換結果を格納するstd::tm構造体への参照。
 * @param milliseconds 変換結果を格納するミリ秒への参照。
 * @return 変換に成功した場合はtrue、無効な形式の場合はfalse。
 */
bool yura::from_uint64_t_to_tm(uint64_t timestamp, std::tm& tm, int& milliseconds) {
    if (timestamp > 99999999999999999ULL) { // YYYYMMDDHHMMSSmmmの桁数チェック
        return false;
    }

    milliseconds = timestamp % 1000;
    uint64_t temp = timestamp / 1000;

    tm.tm_sec = temp % 100;
    temp /= 100;
    tm.tm_min = temp % 100;
    temp /= 100;
    tm.tm_hour = temp % 100;
    temp /= 100;
    tm.tm_mday = temp % 100;
    temp /= 100;
    tm.tm_mon = (temp % 100) - 1; // tm_monは0から始まる
    temp /= 100;
    tm.tm_year = (temp % 10000) - 1900; // tm_yearは1900年からの年数
    tm.tm_isdst = -1; // mktimeに夏時間判定を任せる

    // mktimeでの変換が失敗する可能性を考慮し、ここでは単純な抽出のみ行う
    return true;
}

/**
 * @brief YYYYMMDDHHMMSSmmm形式のuint64_tのstartとendの差をミリ秒で求めます。
 * @param start 開始時刻（uint64_t）。
 * @param end 終了時刻（uint64_t）。
 * @return startとendの差のミリ秒。start > endの場合は負の値になります。
 * @throw std::invalid_argument 無効なタイムスタンプが入力された場合にスローされます。
 */
int64_t yura::diff_milli_secound(uint64_t start, uint64_t end) {
    std::tm start_tm{}, end_tm{};
    int start_ms = 0, end_ms = 0;

    if (!from_uint64_t_to_tm(start, start_tm, start_ms)) {
        throw std::invalid_argument("Invalid start timestamp");
    }
    if (!from_uint64_t_to_tm(end, end_tm, end_ms)) {
        throw std::invalid_argument("Invalid end timestamp");
    }

    // std::time_tに変換して秒単位の差分を計算
    std::time_t start_t = std::mktime(&start_tm);
    std::time_t end_t = std::mktime(&end_tm);

    if (start_t == -1 || end_t == -1) {
        throw std::invalid_argument("Could not convert timestamps to time_t");
    }

    // 秒単位の差にミリ秒の差を足して、全体のミリ秒差分を算出
    int64_t diff_seconds = static_cast<int64_t>(end_t - start_t);
    int64_t diff_ms = static_cast<int64_t>(end_ms - start_ms);

    return diff_seconds * 1000 + diff_ms;
}

// e29480	─	━	│	┃	┄	┅	┆	┇	┈	┉	┊	┋	┌	┍	┎	┏
// e29490	┐	┑	┒	┓	└	┕	┖	┗	┘	┙	┚	┛	├	┝	┞	┟
// e294a0	┠	┡	┢	┣	┤	┥	┦	┧	┨	┩	┪	┫	┬	┭	┮	┯
// e294b0	┰	┱	┲	┳	┴	┵	┶	┷	┸	┹	┺	┻	┼	┽	┾	┿
// e29580	╀	╁	╂	╃	╄	╅	╆	╇	╈	╉	╊	╋	╌	╍	╎	╏
// e29590	═	║	╒	╓	╔	╕	╖	╗	╘	╙	╚	╛	╜	╝	╞	╟
// e295a0	╠	╡	╢	╣	╤	╥	╦	╧	╨	╩	╪	╫	╬	╭	╮	╯
// e295b0	╰	╱	╲	╳	╴	╵	╶	╷	╸	╹	╺	╻	╼	╽	╾	╿
// e29680	▀	▁	▂	▃	▄	▅	▆	▇	█	▉	▊	▋	▌	▍	▎	▏
// e29690	▐	░	▒	▓	▔	▕	▖	▗	▘	▙	▚	▛	▜	▝	▞	▟
// e296a0	■	□	▢	▣	▤	▥	▦	▧	▨	▩	▪	▫	▬	▭	▮	▯
    // "▖" "▗" "▘" "▝" "▙" "▚" "▛" "▜" "▞" "▟" "▐" "▎"
int yura::exec(std::string& cmd) {
    yura_pipe pipe;
    pipe.exec(cmd);
    return 0;
}

bool yura::is_all_whitespace(const std::string& str) {
    return (str.find_first_not_of(" \t\r\n") == std::string::npos);
}

