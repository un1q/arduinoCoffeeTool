#ifndef ACTION_MELODY_H_
#define ACTION_MELODY_H_

#include "melody.h"
#include "action.h"

class ActionMelody : public Action {
  public:
    Melody *melody;
    
    ActionMelody(Melody *melody);
    ~ActionMelody();
    void doIt();
};

#endif