#include "ivvi.hpp"




void ivvi::setup() {
    std::cout << "ivvi setup" << std::endl;
    auto [width, height] = yura.get_term_size();
 
    std::cout << "Terminal size: " << width << "x" << height << std::endl;
    auto ch0 = yura.get_char();
    auto ch1 = yura.get_char();
    std::cout << "ch0 = " << ch0 << "ch1 = " << ch1 << std::endl; 
    std::cout << yura.esc_cursor(2, 2) << ch1;
  }

int ivvi::loop() {
    //std::cout << "ivvi loop" << std::endl;
    auto ch =yura.get_char();
    if (ch == 'g') {
      lc++;
    } else if (ch == 's') {
      lc--;
    } else if (ch == 'f') {
      lr++;
    } else if (ch == 'd') {
      lr--;
    }
    std::cout << yura.esc_cursor(lr, lc);

    return 1;
}