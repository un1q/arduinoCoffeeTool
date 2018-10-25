#include "core.h"

Core::Core(AlarmTimer* timer, Temperature* temp, Keyboard* keyboard, Lcd* lcd) {
  this->timer      = timer;
  this->temp       = temp ;
  this->keyboard   = keyboard;
  this->lcd        = lcd;
  this->screenMain = new ScreenMain(lcd);
}

Core::~Core() {
  delete(screenMain);
}

void Core::loop() {
  keyboard->setShiftMode(shift_off);
  keyboard->loop();
  char k = keyboard->getKey();
  switch (k) {
    case '#': timer->startDrip();
      break;
    case '0': timer->stop();
      break;
    case '4': // left
    case '6': // right
    case '2': // up
    case '8': // bottom
      break;
  }
  timer->loop();
  temp ->loop();
  printMainScreen();
}

void Core::printMainScreen() {
  screenMain->printTemp(temp->getTemp());
  screenMain->printTimer(timer->getSecondsTotal());
  screenMain->printWeight("   0g");
  screenMain->printAlarmTemp("none");
  screenMain->printAlarmTimer("drip");
  screenMain->printAlarmWeight("none");
}