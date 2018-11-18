#ifndef MAIN_LOOP_H_
#define MAIN_LOOP_H_

// main loop
//
// Knows with screen is active (main screen, main menu screen, etc) and
// calls right Core class (CoreMain, CoreMainMenu, etc)

#include "globals.h"
#include "core_main.h"
#include "core_main_menu.h"
#include "core.h"

extern CoreMain     coreMain;
extern CoreMainMenu coreMainMenu;
extern Core         *core;

void changeCore(Core *core);

void mainLoopStartup();
void mainLoop();

#endif