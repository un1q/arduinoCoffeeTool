#ifndef MULTI_ALARM_H_
#define MULTI_ALARM_H_

#include "alarm.h"

class MultiAlarm {
  public:
    Alarm *alarms     = nullptr; //array
    int   alarmsCount = 0;
    
    void   reset();
    bool   check(int value);
    int    difference(int value);
    Alarm* getNext(int value);
};

#endif