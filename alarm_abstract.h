#ifndef ALARM_ABSTRACT_H_
#define ALARM_ABSTRACT_H_

#include "action.h"

class AlarmAbstract {
  public:
    virtual ~AlarmAbstract();
    virtual void reset()            = 0;
    virtual bool check(int value)   = 0;
    virtual int  remains(int value) = 0;
};

#endif