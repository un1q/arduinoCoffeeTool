#ifndef CORE_H_
#define CORE_H_

#include "core_timer.h"
#include "core_temp.h"
#include "keyboard.h"
#include "lcd.h"
#include "screen_main.h"

class Core {
    CoreTimer  *timer;
    CoreTemp   *temp;
    Lcd        *lcd;
    Keyboard   *keyboard;
    ScreenMain *screenMain;
  public:
    Core(CoreTimer*, CoreTemp*, Keyboard*, Lcd*);
    ~Core();
    void loop();
};

#endif