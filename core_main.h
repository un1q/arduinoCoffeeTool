#ifndef CORE_MAIN_H_
#define CORE_MAIN_H_

// Main screen
// Presents all sensors output and all alarms on LCD
// Calls void (*gotoMenu)() when main menu should be presented
// User can also start timer in this mode

#include "alarm_timer.h"
#include "temperature.h"
#include "keyboard.h"
#include "lcd.h"
#include "core.h"
#include "measure_weight.h"

class CoreMain : public Core {
    AlarmTimer    *alarmTimer;
    Temperature   *temp;
    MeasureWeight *measureWeight;
    Keyboard      *keyboard;
    Lcd           *lcd;
    Lcd::Info     lcdInfo;
    void printMainScreen();
  public:
    void (*gotoMenu)() = {};
    CoreMain(AlarmTimer*, Temperature*, MeasureWeight*, Keyboard*, Lcd*);
    ~CoreMain();
    void update(char key);
    void start();
    void usePreset(int i);
};

#endif