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
        int char_bytes = get_char_bytes(first_byte);

        if (current_byte + char_bytes > str.length()) {
            // 文字列の終わりを超えた
            throw std::out_of_range("UTF8 characters is outside the range of the string.");
        }

        current_byte += char_bytes;
        processed_chars++;
    }
    return current_byte - start_byte;
}

int jap54::get_utf8_term_width(const std::string& str, size_t start_byte, int utf8_size) {
    if (start_byte < 0 || start_byte >= str.length()) {
        throw std::out_of_range("The startting byte postion is outside the range of the string.");
    }
    if (utf8_size <= 0) {
        throw std::invalid_argument("The number of characters in a UTF-8 encoding must be a positive number.");
    }

    size_t current_byte = start_byte;
    int processed_chars = 0;
    int term_width = 0;
    while (processed_chars < utf8_size && current_byte < str.length()) {
        unsigned char first_byte = static_cast<unsigned char>(str[current_byte]);
        int char_bytes = get_char_bytes(first_byte);

        if (current_byte + char_bytes > str.length()) {
            // 文字列の終わりを超えた
            throw std::out_of_range("UTF8 characters is outside the range of the string.");
        }

        current_byte += char_bytes;
        processed_chars++;
        if (char_bytes == 1) {
            term_width += 1;
        } else {
            term_width += 2;
        }
    }
    return current_byte - start_byte;
}

uint32_t jap54::hash32(const void* data, size_t size) {
    auto bytes = static_cast<const uint8_t*>(data);
    uint32_t hash = 2166136261U; // offset_basis

    for (size_t i = 0; i < size; ++i) {
        hash ^= bytes[i];
        hash *= 16777619U;        // FNV_prime
    }
    return hash;
}
