#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include "task.hpp"
#include "ivvi.hpp"

  
int main() {

  ivvi iv;
  task_mng mng;

  mng.add_task(iv);
  mng.setup();
  mng.loop();

  return 0;
}
