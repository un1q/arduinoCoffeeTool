#include "core_main.h"

CoreMain::CoreMain(AlarmTimer* alarmTimer, Temperature* temp, MeasureWeight *measureWeight, Keyboard* keyboard, Lcd* lcd) {
  this->alarmTimer    = alarmTimer;
  this->temp          = temp ;
  this->keyboard      = keyboard;
  this->lcd           = lcd;
  this->measureWeight = measureWeight;
}

CoreMain::~CoreMain() {
}

void CoreMain::start() {
  keyboard->setShiftMode(shift_always);
}

void CoreMain::update(char key) {
  switch (key) {
    case k_ENTER:
    case k_CLEAR:
      alarmTimer->start();
      break;
    case '0': 
    case '.': 
      alarmTimer->stop();
      measureWeight->tare();
      break;
    case k_F1:
      alarmTimer->usePreset(&TimerPreset::drip);
      break;
    case k_F2:
      alarmTimer->usePreset(&TimerPreset::chemex);
      break;
    case k_F3:
      alarmTimer->usePreset(&TimerPreset::tea);
      break;
    case k_F4:
      alarmTimer->usePreset(&TimerPreset::fellow);
      break;
//      gotoMenu();
//      return;
  }
  Serial.println(key);
  alarmTimer->loop();
  temp ->loop();
  printMainScreen();
}

void CoreMain::printMainScreen() {
  lcdInfo.temp        = temp->getTemp();
  lcdInfo.time        = alarmTimer->measureTime->getSecondsTotal();
  lcdInfo.weight      = measureWeight->get();
  lcdInfo.tempAlarm   = "none";
  lcdInfo.timeAlarm   = alarmTimer->toString();
  lcdInfo.weightAlarm = "none";
  lcd->print(&lcdInfo);
}
