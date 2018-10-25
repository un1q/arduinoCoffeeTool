#ifndef CORE_TIMER_H_
#define CORE_TIMER_H_

#include "melody.h"
#include "timer.h"

class CoreTimer {
    Timer  timer;
    Melody *melody;
    Melody *buzz;
    int*   dripTiming      = new int[4] {3, 33, 33+60, 33+60+90};
    int    dripTimingCount = 4;
    bool   buzzed          = false;
  public:
    CoreTimer(Melody *melody, Melody *buzz);
    void loop();
    int  getSecondsTotal();
    void startDrip();
    void stop();
};

#endif