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
    const static TimerPreset fellow;
    const static int PRESETS_COUNT = 4;
    const static TimerPreset* all[PRESETS_COUNT];
    
    TimerPreset(int startAt, char* name, int alarms[], int alarmsCount);
    TimerPreset(int startAt, char* name, int alarms[], int alarmsCount, int buzzers[], int buzzersCount);
};

#endif