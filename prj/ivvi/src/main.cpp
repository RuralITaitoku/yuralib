#include "task.hpp"
#include "ivvi.hpp"
#include "yura25.hpp"
#include <fstream>
#include <sstream>



bool test_split(std::vector<std::string>& args) {

  for (auto file_name : args) {
    DP(file_name);
    auto data = yura::load(file_name);
    auto lines = yura::split(data);
    for (auto line : lines) {
      DP(line);
    }
  }
  std::string input;
  std::getline(std::cin, input);
  if (input == "q") {
    return false;
  }
  return true;
}

int main(int argc, char** argv) {
  ivvi iv;
  task_mng mng;
  std::map<std::string, std::string> circle;
  std::vector<std::string> args;
  for (int i = 1; i < argc; i++) {
    args.push_back(argv[i]);
  }
  if (!test_split(args)) {
    return 0;
  }
  mng.add_task(iv.screen);
  mng.add_task(iv);
  mng.setup();
  mng.loop(circle);

  return 0;
}
