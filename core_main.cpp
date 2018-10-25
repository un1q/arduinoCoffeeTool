#include "core_main.h"

CoreMain::CoreMain(AlarmTimer* timer, Temperature* temp, Keyboard* keyboard, ScreenMain* screen) {
  this->timer      = timer;
  this->temp       = temp ;
  this->keyboard   = keyboard;
  this->screen     = screen;
}

CoreMain::~CoreMain() {
  delete(screen);
}

void CoreMain::start() {
  screen->start();
  keyboard->setShiftMode(shift_off);
}

void CoreMain::update(char key) {
  switch (key) {
    case '#': timer->startDrip();
      break;
    case '0': timer->stop();
      break;
    case '4': // left
    case '6': // right
    case '2': // up
    case '8': // bottom
      gotoMenu();
      return;
  }
  timer->loop();
  temp ->loop();
  printMainScreen();
}

void CoreMain::printMainScreen() {
  screen->printTemp(temp->getTemp());
  screen->printTimer(timer->getSecondsTotal());
  screen->printWeight("   0g");
  screen->printAlarmTemp("none");
  screen->printAlarmTimer("drip");
  screen->printAlarmWeight("none");
}
