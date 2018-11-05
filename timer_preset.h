#ifndef TIMER_PRESET_H_
#define TIMER_PRESET_H_

#include "multi_alarm.h"
#include "action.h"

struct TimerPreset {
    int  *buzzers;
    int  buzzersCount;
    int  *alarms;
    int  alarmsCount;
    char *name;
    int  startAt;
    
    const static TimerPreset drip;
    const static TimerPreset chemex;
    const static TimerPreset tea;
    
    TimerPreset(int startAt, char* name, int alarms[], int alarmsCount);
    TimerPreset(int startAt, char* name, int alarms[], int alarmsCount, int buzzers[], int buzzersCount);
};

#endif