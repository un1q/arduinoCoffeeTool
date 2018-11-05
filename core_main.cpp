#include "core_main.h"

CoreMain::CoreMain(AlarmTimer* alarmTimer, Temperature* temp, Keyboard* keyboard, Lcd* lcd) {
  this->alarmTimer       = alarmTimer;
  this->temp             = temp ;
  this->keyboard         = keyboard;
  this->lcd              = lcd;
}

CoreMain::~CoreMain() {
}

void CoreMain::start() {
  keyboard->setShiftMode(shift_off);
}

void CoreMain::update(char key) {
  switch (key) {
    case '#': alarmTimer->start();
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
  lcdInfo.temp        = temp->getTemp();
  lcdInfo.time        = alarmTimer->measureTime->getSecondsTotal();
  lcdInfo.weight      = 0;
  lcdInfo.tempAlarm   = "none";
  lcdInfo.timeAlarm   = alarmTimer->toString();
  lcdInfo.weightAlarm = "none";
  lcd->print(&lcdInfo);
}
