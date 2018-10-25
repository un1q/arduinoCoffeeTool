#ifndef CORE_MAIN_MENU_H_
#define CORE_MAIN_MENU_H_

#include "alarm_timer.h"
#include "temperature.h"
#include "keyboard.h"
#include "screen_main.h"
#include "core.h"

class CoreMainMenu : public Core {
    AlarmTimer    *timer;
    Temperature   *temp;
    Keyboard      *keyboard;
    ScreenMain    *screen;
    void printMainScreen();
  public:
    void (*goBack)() = {};
    CoreMainMenu(AlarmTimer*, Temperature*, Keyboard*, ScreenMain*);
    ~CoreMainMenu();
    void update(char key);
    void start();
};

#endif