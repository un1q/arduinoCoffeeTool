#ifndef CORE_MAIN_MENU_H_
#define CORE_MAIN_MENU_H_

// Main menu
// menu presents all available option on LCD at once:
//  - set temperature alarm
//  - set weight alarm
//  - set timer alarm/mode
//  - use preset
//  - go back to main screen

#include "globals.h"
#include "core.h"

class CoreMainMenu : public Core {
    Lcd::Menu     menu;
    void printMainScreen();
  public:
    CoreMainMenu();
    ~CoreMainMenu();
    int  update(char key);
    void start();
};

#endif