#include "core_main.h"

CoreMain::CoreMain(AlarmTimer* alarmTimer, Temperature* temp, Keyboard* keyboard, ScreenMain* screen) {
  this->alarmTimer = alarmTimer;
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
    case '#': alarmTimer->startDrip();
      break;
    case '0': alarmTimer->stop();
      break;
    case '4': // left
    case '6': // right
    case '2': // up
    case '8': // bottom
      gotoMenu();
      return;
  }
  alarmTimer->loop();
  temp ->loop();
  printMainScreen();
}

void CoreMain::printMainScreen() {
  screen->printTemp(temp->getTemp());
  screen->printTimer(alarmTimer->getSecondsTotal());
  screen->printWeight("   0g");
  screen->printAlarmTemp("none");
  screen->printAlarmTimer(alarmTimer->toString());
  screen->printAlarmWeight("none");
}
