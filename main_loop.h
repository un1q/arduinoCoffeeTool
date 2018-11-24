#ifndef MAIN_LOOP_H_
#define MAIN_LOOP_H_

// main loop
//
// Knows with screen is active (main screen, main menu screen, etc) and
// calls right Core class (CoreMain, CoreMainMenu, etc)

#include "core.h"

extern Core         *core;

void changeCore(int coreId);

void mainLoopStartup();
void mainLoop();
void logSensors();

#endif