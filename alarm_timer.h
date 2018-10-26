#ifndef ALARM_TIMER_H_
#define ALARM_TIMER_H_

#include "melody.h"
#include "timer.h"

class AlarmTimer {
    Timer  timer;
    Melody *melody;
    Melody *buzz;
    int*   dripTiming      = new int[4] {3, 33, 33+60, 33+60+90};
    int    dripTimingCount = 4;
    bool   buzzed          = false;
  public:
    AlarmTimer(Melody *melody, Melody *buzz);
    void loop();
    int  getSecondsTotal();
    void startDrip();
    void stop();
    char* toString();
};

#endif