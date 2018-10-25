#ifndef CORE_MAIN_H_
#define CORE_MAIN_H_

#include "alarm_timer.h"
#include "temperature.h"
#include "keyboard.h"
#include "screen_main.h"
#include "core.h"

class CoreMain : public Core {
    AlarmTimer    *timer;
    Temperature   *temp;
    Keyboard      *keyboard;
    ScreenMain    *screen;
    
    void printMainScreen();
  public:
    void (*gotoMenu)() = {};
    CoreMain(AlarmTimer*, Temperature*, Keyboard*, ScreenMain*);
    ~CoreMain();
    void update(char key);
    void start();
};

#endif