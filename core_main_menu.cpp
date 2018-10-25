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
}

void CoreMainMenu::update(char key) {
  switch (key) {
    case '#':
    case '0':
      goBack();
      return;
  }
  timer->loop();
  temp ->loop();
  printMainScreen();
}

void CoreMainMenu::printMainScreen() {
  screen->printTemp(temp->getTemp());
  screen->printTimer(timer->getSecondsTotal());
  screen->printWeight("   0g");
  screen->printAlarmTemp("????");
  screen->printAlarmTimer("????");
  screen->printAlarmWeight("????");
}
