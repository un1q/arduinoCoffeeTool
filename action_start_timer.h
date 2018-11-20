#ifndef ACTION_START_TIMER_H_
#define ACTION_START_TIMER_H_

#include "action.h"

class ActionStartTimer: public Action {
  public:
    ActionStartTimer();
    ~ActionStartTimer();
    void doIt();
};

#endif