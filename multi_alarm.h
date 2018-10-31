#ifndef MULTI_ALARM_H_
#define MULTI_ALARM_H_

#include "alarm.h"

class MultiAlarm {
  public:
    Alarm *alarms     = nullptr; //array
    int   alarmsCount = 0;
    
    bool check(int value);
};

#endif