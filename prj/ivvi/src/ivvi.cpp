#include <thread>
#include "ivvi.hpp"
#include <codecvt>
#include <locale>
#include <array>


void ivvi_screen::setup() {
  auto [w, h] = yura.get_term_size();
  width = w;
  height = h;
  data.resize(w * h, static_cast<uint64_t>(' '));
  draw_line(1, 1, 100, 30, 'a');
}
int ivvi_screen::loop(std::map<std::string, std::string>& circle) {
  //std::cout << yuraterm::esc_home() << "ivvi_screen" << millis() << std::endl;
  std::string line;
  std::cout << yura.esc_cursor(1, 1) ; 
  for (int i = 0; i < height; i++) {
    line = "";
    for (int j = 0; j < width; j++) {
      auto ch = data[(i * width) + j];
      if (ch < 0x80) {
        line += static_cast<char>(ch);
      }
    }
    std::cout << line << std::endl;
  }

  std::cout << yura.esc_cursor(cursor_row, cursor_col) ; 
  return 1000;
}




void ivvi_screen::cursor(int r, int c) {
    cursor_row = r;
    cursor_col = c;
}

void ivvi_screen::validate() {
  screen_update = true;
  next(0);
}

std::string ivvi_screen::get(uint64_t ch) {
  std::string result;
  result += static_cast<char>(ch);
  return result;
}

/**
 * @brief UTF8の文字列の指定位置のUTF8一文字を返す。
 * @param utf8 UTF8の文字列
 * @param index 文字の位置。
 * @return UTF8の一文字
 */
std::string ivvi_screen::get_utf8(std::string& utf8, int index) {
    int byte_size = next_utf8(utf8, index);
    return utf8.substr(index, (byte_size - index));
}

int ivvi_screen::next_utf8(std::string& utf8, int index) {
  if (index < 0) {
    throw std::out_of_range("Index out of range");
  }
  int utf8_length = utf8.length();
  unsigned char first_byte = static_cast<unsigned char>(utf8[index]);
  int byte_size;
  if ((first_byte >> 7) == 0b0) { // 0xxxxxxx (1 byte)
    byte_size = 1;
  } else if ((first_byte >> 5) == 0b110) { // 110xxxxx (2 bytes)
    byte_size = 2;
  } else if ((first_byte >> 4) == 0b1110) { // 1110xxxx (3 bytes)
    byte_size = 3;
  } else if ((first_byte >> 3) == 0b11110) { // 11110xxx (4 bytes)
    byte_size = 4;
  } else if ((first_byte >> 2) == 0b111110) { // 111110xxx (5 bytes)
    byte_size = 5;
  } else if ((first_byte >> 1) == 0b1111110) { // 1111110xxx (6 bytes)
    byte_size = 5;
  } else {
    throw std::runtime_error("Invalid UTF-8 encoding");
  }
  if (index + byte_size > utf8_length) {
    throw std::runtime_error("Invalid UTF-8 encoding: incomplete character");
  }
  return index + byte_size;
}

/**
 * @brief UTF8のコードをstd::stringに変換する
 * @param utf8 一文字のUTF-8コード
 * @return 一文字の文字列。変換に失敗した場合は空文字列を返す。
 */
std::string ivvi_screen::get_string(uint64_t utf8, bool little_endian) {
  std::string byte_string(8, '\0');
  for (size_t i = 0; i < 8; ++i) {
    byte_string[i] = static_cast<char>((utf8 >> (i * 8)) & 0xFF);
  }
  if (little_endian) {
    std::reverse(byte_string.begin(), byte_string.end());
  }
  return byte_string;
}

uint64_t ivvi_screen::get_int64(std::string& utf8) {
  uint64_t result = 0;
  int byte_size = next_utf8(utf8, 0);
  for (int i = 0; i < byte_size; i++) {
    result <<= 8;
    result += static_cast<uint64_t>(utf8[i]);
  }
  return result;
}

void ivvi_screen::put(int x, int y, uint64_t ch) {
  int r = std::max(0, y + 1);
  r = std::min(height, r);
  int c = std::max(0, x + 1);
  c = std::min(width, c);

  data[width * (r - 1) + c - 1] = ch;
}

/**
 * @brief 線を描画する
 * (x1,y1)〜(x2,y2)の間に線を引きます。点の描画はput(int x, int y, uint64_t ch)
 * @param x1 線の始点のx座標
 * @param y1 線の始点のy座標
 * @param x2 線の終点のx座標
 * @param y2 線の終点のy座標
 * @param ch 線を構成する文字コード
 */
void ivvi_screen::draw_line(int x1, int y1, int x2, int y2, uint64_t ch) {
  int dx = std::abs(x2 - x1);
  int dy = std::abs(y2 - y1);
  int sx = (x1 < x2) ? 1 : -1;
  int sy = (y1 < y2) ? 1 : -1;
  int err = dx - dy;

  // 始点と終点が画面外の場合は何もしない
  if ((x1 < 0 || x1 >= width || y1 < 0 || y1 >= height) &&
    (x2 < 0 || x2 >= width || y2 < 0 || y2 >= height)) {
    return;
  }
  while (true) {
    put(x1, y1, ch);
    if (x1 == x2 && y1 == y2) break;
    int e2 = 2 * err;
    if (e2 > -dy) {
      err = err - dy;
      x1 = x1 + sx;
    }
    if (e2 < dx) {
      err = err + dx;
      y1 = y1 + sy;
    }
  }
}

void ivvi_screen::draw_string(int x, int y, std::string str) {
  int index = 0;
  std::string str_utf8 = get_utf8(str, index);
  int byte_size = str_utf8.length();
  
}




void ivvi::setup() {
}

int ivvi::loop(std::map<std::string, std::string>& circle) {
    //std::cout << "ivvi loop" << std::endl;
    char ch = screen.yura.get_char();

    if (ch == 'g') {
      lc++;
      screen.validate();
    } else if (ch == 's') {
      lc--;
      screen.validate();
    } else if (ch == 'f') {
      lr++;
      screen.validate();
    } else if (ch == 'd') {
      lr--;
      screen.validate();
    } else if (ch == 'w') {
      int result = system("w3m https://www.google.com/");
      if (result == 0) {
        std::cout << "コマンドの実行に成功しました。" << std::endl;
      } else {
        std::cout << "コマンドの実行に失敗しました。" << std::endl;
      }
    
    } else if (ch == 'q') {
      circle["mng"] += "quit;";
    }
    lc = std::max(1, lc);
    lc = std::min(screen.width, lc);
    lr = std::max(1, lr);
    lr = std::min(screen.height, lr);
    screen.cursor(lr, lc);
    return 10;
}