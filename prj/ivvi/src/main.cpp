#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>
#include "yuraterm.hpp"
#include "task.hpp"  

typedef struct {
  int width;
  int height;
  std::vector<char> screen;
} screen;

void init(screen& s, int w, int h, char ch = ' ') {
  s.width = w;
  s.height = h;
  s.screen.resize(w * h, ' ');
}

class Dog : public task {
  public:
      void setup() override {
        std::cout << "setupワンワン " << millis() << std::endl;
      }
      int loop() override {
          std::cout << "ワンワン " << millis() << std::endl;
          return 1000;
      }
  };
  
  class Cat : public task {
  public:
      void setup() override {
        std::cout << "setupニャーニャー " << millis() << std::endl;
      }
      int loop() override {
          std::cout << "ニャーニャー " << millis() << std::endl;
          return 3300;
      }
  };
  
int main() {
  task_mng mng;

  Dog dog;
  Cat cat;
  mng.add_task(dog);
  mng.add_task(cat);

  mng.setup();
  mng.loop();




  for (;;) {



    std::string input;
    std::cin >> input;
    if (input == "q") {
      break;
    }
  }
  return 0;

  /*
  auto [width, height] = yura.get_term_size();
 
  std::cout << "Terminal size: " << width << "x" << height << std::endl;
  auto ch0 = yura.get_char();
  auto ch1 = yura.get_char();
  std::cout << "ch0 = " << ch0 << "ch1 = " << ch1 << std::endl; 
  std::cout << yura.esc_cursor(2, 2) << ch1;
  int lr = 3;
  int lc = 3;
  for(;;) {
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
  }
  */
}
