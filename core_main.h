#ifndef CORE_MAIN_H_
#define CORE_MAIN_H_

// Main screen
// Presents all sensors output and all alarms on LCD
// Calls void (*gotoMenu)() when main menu should be presented
// User can also start timer in this mode

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