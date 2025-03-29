#ifndef __IVVI_HPP_
#define __IVVI_HPP_
#include "yuraterm.hpp"
#include "task.hpp"

class ivvi : public task {
    yuraterm yura;
    int lr = 3;
    int lc = 3;
  
public:

    void setup() override;
    int loop() override;
};




#endif
