
#include "yura25.hpp"
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






int get_utf8_byte_size(const std::string& str, int start_byte, int utf8_size = 1) {
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