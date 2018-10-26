#ifndef ALARM_TIMER_H_
#define ALARM_TIMER_H_

// Setting and checking timer alarm.
// Alarm can be complex, for example: play melody after 30,90 and 120 seconds
// Alarm also buzzes 10 seconds before each alarm

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