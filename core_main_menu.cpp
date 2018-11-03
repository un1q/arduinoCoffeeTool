#include "core_main_menu.h"

CoreMainMenu::CoreMainMenu(AlarmTimer* timer, Temperature* temp, Keyboard* keyboard, Lcd* lcd) {
  this->timer      = timer;
  this->temp       = temp ;
  this->keyboard   = keyboard;
  this->lcd        = lcd;
}

CoreMainMenu::~CoreMainMenu() {
}

void CoreMainMenu::start() {
  keyboard->setShiftMode(shift_off);
  //screen->startMainMenuSelection();
  menu.options  = nullptr;
  menu.size     = 0;
  menu.selected = 0;
}

void CoreMainMenu::update(char key) {
  switch (key) {
    //case '4': screen->selectLeft (); break;
    //case '6': screen->selectRight(); break;
    //case '2': screen->selectUp   (); break;
    //case '8': screen->selectDown (); break;
    case '0': goBack(); return;
  }
  timer->loop();
  temp ->loop();
  printMainScreen();
}

void CoreMainMenu::printMainScreen() {
  lcd->print(&menu);
  //screen->printPresetOption();
  //screen->printBackOption();
  //screen->printAlarmTemp("none");
  //screen->printAlarmTimer(timer->toString());
  //screen->printAlarmWeight("none");
}
