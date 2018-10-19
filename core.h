#ifndef CORE_H_
#define CORE_H_

#include "lcd.h"

class Core {
  protected:
    Lcd      *lcd;
  public:
    virtual void setup(Lcd *lcd);
    virtual void loop(char key)  = 0;
    virtual void start()         = 0;
};

#endif