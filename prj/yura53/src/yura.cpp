#include "yura.hpp"
#include <stdexcept>

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
int yura::get_utf8_byte_size(const std::string& str, int start_byte, int utf8_size) {
    if (start_byte < 0 || start_byte >= str.length()) {
        throw std::out_of_range("開始バイト位置が文字列の範囲外です。");
    }
    if (utf8_size <= 0) {
        throw std::invalid_argument("UTF8の文字数は正の数である必要があります。");
    }

    int current_byte = start_byte;
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

  