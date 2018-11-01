#ifndef ALARM_H_
#define ALARM_H_

#include "action.h"
#include "alarm_abstract.h"

class Alarm : public AlarmAbstract {
    int    direction = 0;
  public:
    int    alarmValue;
    Action *alarmAction;
    
    Alarm(Action *alarmAction, int alarmValue);
    virtual ~Alarm();
    virtual void reset();
    virtual bool check(int value);
    virtual int  remains(int value);
};

#endif