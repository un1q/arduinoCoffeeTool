#include "core_main_menu.h"

CoreMainMenu::CoreMainMenu(AlarmTimer* timer, Temperature* temp, Keyboard* keyboard, ScreenMain* screen) {
  this->timer      = timer;
  this->temp       = temp ;
  this->keyboard   = keyboard;
  this->screen     = screen;
}

CoreMainMenu::~CoreMainMenu() {
  delete(screen);
}

void CoreMainMenu::start() {
  screen->start();
  keyboard->setShiftMode(shift_off);
  screen->startMainMenuSelection();
}

void CoreMainMenu::update(char key) {
  switch (key) {
    case '4': screen->selectLeft (); break;
    case '6': screen->selectRight(); break;
    case '2': screen->selectUp   (); break;
    case '8': screen->selectDown (); break;
    case '0': goBack(); return;
  }
  timer->loop();
  temp ->loop();
  printMainScreen();
}

void CoreMainMenu::printMainScreen() {
  screen->printPresetOption();
  screen->printBackOption();
  screen->printAlarmTemp("none");
  screen->printAlarmTimer(timer->toString());
  screen->printAlarmWeight("none");
}
