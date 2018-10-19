#ifndef CORE_TIMER_H_
#define CORE_TIMER_H_

#include "melody.h"
#include "core.h"

class CoreTimer : public Core {
    Timer  timer;
    Melody *melody;
    Melody *buzz;
    int*   dripTiming      = new int[4] {3, 33, 33+60, 33+60+90};
    int    dripTimingCount = 4;
  public:
    CoreTimer(Melody *melody, Melody *buzz);
    void loop(char key);
    void start();
};

#endif