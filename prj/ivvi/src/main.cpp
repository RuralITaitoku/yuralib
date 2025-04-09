#include "task.hpp"
#include "ivvi.hpp"

  
int main() {

  ivvi iv;
  task_mng mng;
  std::map<std::string, std::string> circle;

  mng.add_task(iv.screen);
  mng.add_task(iv);
  mng.setup();
  mng.loop(circle);

  return 0;
}
