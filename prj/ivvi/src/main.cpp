#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include "yuraterm.hpp"



int main() {
  yuraterm yura;


  auto [width, height] = yura.get_term_size();
 
  std::cout << "Terminal size: " << width << "x" << height << std::endl;
  auto ch0 = yura.get_char();
  auto ch1 = yura.get_char();
  std::cout << "ch0 = " << ch0 << "ch1 = " << ch1 << std::endl; 
  return 0;
}