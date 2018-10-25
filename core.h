#ifndef CORE_H_
#define CORE_H_

#include "core_timer.h"
#include "core_temp.h"
#include "keyboard.h"
#include "lcd.h"

class Core {
    CoreTimer *timer;
    CoreTemp  *temp;
    Lcd       *lcd;
    Keyboard  *keyboard;
  public:
    Core(CoreTimer*, CoreTemp*, Keyboard*, Lcd*);
    void loop();
};

#endif