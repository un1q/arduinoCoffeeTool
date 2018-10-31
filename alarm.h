#ifndef ALARM_H_
#define ALARM_H_

#include "action.h"

class Alarm {
    int    direction = 0;
  public:
    int    alarmValue;
    Action *alarmAction;
    
    Alarm(Action *alarmAction, int alarmValue);
    bool check(int value);
    int  difference(int value);
};

#endif