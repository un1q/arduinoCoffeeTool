#ifndef MAIN_LOOP_H_
#define MAIN_LOOP_H_

// main loop
//
// Knows with screen is active (main screen, main menu screen, etc) and
// calls right Core class (CoreMain, CoreMainMenu, etc)

#include "alarm_timer.h"
#include "temperature.h"
#include "keyboard.h"
#include "lcd.h"
#include "core_main.h"
#include "core_main_menu.h"
#include "core.h"

class MainLoop {
    AlarmTimer   *timer;
    Temperature  *temp;
    Lcd          *lcd;
    Keyboard     *keyboard;
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