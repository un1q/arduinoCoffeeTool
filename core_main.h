#ifndef CORE_MAIN_H_
#define CORE_MAIN_H_

// Main screen
// Presents all sensors output and all alarms on LCD
// Calls void (*gotoMenu)() when main menu should be presented
// User can also start timer in this mode

#include "globals.h"
#include "alarm_timer.h"
#include "core.h"

class CoreMain : public Core {
    AlarmTimer    *alarmTimer;
    Lcd::Info     lcdInfo;
    void printMainScreen();
  public:
    void (*gotoMenu)() = {};
    CoreMain(AlarmTimer*);
    ~CoreMain();
    void update(char key);
    void start();
    void usePreset(int i);
};

#endif