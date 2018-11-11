#ifndef MAIN_LOOP_H_
#define MAIN_LOOP_H_

// main loop
//
// Knows with screen is active (main screen, main menu screen, etc) and
// calls right Core class (CoreMain, CoreMainMenu, etc)

#include "globals.h"
#include "alarm_timer.h"
#include "core_main.h"
#include "core_main_menu.h"
#include "core.h"
#include "action_melody.h"

class MainLoop {
    AlarmTimer    *alarmTimer;
    ActionMelody  *alarmAction;
    ActionMelody  *buzzAction;
    static CoreMain     *coreMain;
    static CoreMainMenu *coreMainMenu;
    static Core         *core;
    
    static void changeCore(Core *core);
  public:
    MainLoop(Melody* alarmMelody, Melody* buzzMelody);
    ~MainLoop();
    void startup();
    void loop();
};

#endif