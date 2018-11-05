#ifndef TIMER_PRESET_H_
#define TIMER_PRESET_H_

#include "multi_alarm.h"
#include "action.h"

struct TimerPreset {
    int *buzzers;
    int buzzersCount;
    int *alarms;
    int alarmsCount;
    
    const static TimerPreset drip;
    
    TimerPreset(int alarms[], int alarmsCount, int buzzers[], int buzzersCount);
};

#endif