#ifndef MAIN_LOOP_H_
#define MAIN_LOOP_H_

#include "alarm_timer.h"
#include "temperature.h"
#include "keyboard.h"
#include "lcd.h"
#include "screen_main.h"
#include "core_main.h"
#include "core_main_menu.h"
#include "core.h"

class MainLoop {
    AlarmTimer   *timer;
    Temperature  *temp;
    Lcd          *lcd;
    Keyboard     *keyboard;
    ScreenMain   *screen;
    static CoreMain     *coreMain;
    static CoreMainMenu *coreMainMenu;
    static Core         *core;
    
    static void changeCore(Core *core);
  public:
    MainLoop(AlarmTimer*, Temperature*, Keyboard*, Lcd*);
    ~MainLoop();
    void startup();
    void loop();
};

#endif