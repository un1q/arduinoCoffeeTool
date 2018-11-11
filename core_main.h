#ifndef CORE_MAIN_H_
#define CORE_MAIN_H_

// Main screen
// Presents all sensors output and all alarms on LCD
// Calls void (*gotoMenu)() when main menu should be presented
// User can also start timer in this mode

#include "globals.h"
#include "alarm_timer.h"
#include "temperature.h"
#include "core.h"
#include "measure_weight.h"

class CoreMain : public Core {
    AlarmTimer    *alarmTimer;
    Temperature   *temp;
    MeasureWeight *measureWeight;
    Lcd::Info     lcdInfo;
    void printMainScreen();
  public:
    void (*gotoMenu)() = {};
    CoreMain(AlarmTimer*, Temperature*, MeasureWeight*);
    ~CoreMain();
    void update(char key);
    void start();
    void usePreset(int i);
};

#endif