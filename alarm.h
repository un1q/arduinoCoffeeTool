#ifndef ALARM_H_
#define ALARM_H_

#include "action.h"
#include "alarm_abstract.h"

class Alarm : public AlarmAbstract {
  public:
    enum Mode {crossing, crossingUp, crossingDown};
  private:
    int  direction = 0;
    Mode mode      = crossing;
  public:
    int    alarmValue;
    Action *alarmAction;
    
    Alarm(Action *alarmAction, int alarmValue, Mode mode);
    virtual ~Alarm();
    virtual void reset();
    virtual bool check(int value);
    virtual int  remains(int value);
};

#endif