#ifndef ALARM_H_
#define ALARM_H_

#include "action.h"
#include "alarm_abstract.h"

class Alarm : public AlarmAbstract {
  public:
    enum Mode {crossing, crossingUp, crossingDown};
  protected:
    int  direction = 0;
    Mode mode      = crossing;
    bool clicked   = false;
  public:
    int    alarmValue;
    Action *alarmAction;
    
    Alarm(Action *alarmAction, int alarmValue, Mode mode);
    virtual ~Alarm();
    virtual void reset();
    virtual bool check(int value);
    void changeValue(int value);
    
    inline bool isClicked() { return clicked; };
    inline void doIt() { if (alarmAction) alarmAction->doIt(); };
};

#endif