#ifndef CORE_H_
#define CORE_H_

#include "alarm_timer.h"
#include "temperature.h"
#include "keyboard.h"
#include "lcd.h"
#include "screen_main.h"

class Core {
    AlarmTimer  *timer;
    Temperature   *temp;
    Lcd        *lcd;
    Keyboard   *keyboard;
    ScreenMain *screenMain;
    
    void printMainScreen();
  public:
    Core(AlarmTimer*, Temperature*, Keyboard*, Lcd*);
    ~Core();
    void loop();
};

#endif