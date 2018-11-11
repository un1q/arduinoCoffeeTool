#ifndef MULTI_ALARM_H_
#define MULTI_ALARM_H_

#include "alarm.h"
#include "alarm_abstract.h"

class MultiAlarm : public AlarmAbstract {
  public:
    AlarmAbstract **alarms    = nullptr; //array of AlarmAbstract*
    int           alarmsCount = 0;
    
    virtual ~MultiAlarm();
    void           reset();
    bool           check(int value);
    int            remains(int value);
    AlarmAbstract* getNext(int value);
};

#endif