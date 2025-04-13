#include "task.hpp"
#include "ivvi.hpp"

  
int main(int argc, char** argv) {

  ivvi iv;
  task_mng mng;
  std::map<std::string, std::string> circle;
  std::vector<std::string> args;
  for (int i = 0; i < argc; i++) {
    args.push_back(argv[i]);
  }

  mng.add_task(iv.screen);
  mng.add_task(iv);
  mng.setup();
  mng.loop(circle);

  return 0;
}
