#include "core_main.h"

CoreMain::CoreMain(AlarmTimer* alarmTimer, Temperature* temp, MeasureWeight *measureWeight) {
  this->alarmTimer    = alarmTimer;
  this->temp          = temp ;
  this->measureWeight = measureWeight;
}

CoreMain::~CoreMain() {
}

void CoreMain::start() {
  keyboard.setShiftMode(shift_always);
  lcd->clear();
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
    case k_F1: usePreset(0); break;
    case k_F2: usePreset(1); break;
    case k_F3: usePreset(2); break;
    case k_F4: usePreset(3); break;
    case k_F5: usePreset(4); break;
    case k_LEFT: gotoMenu(); return;
  }
  Serial.println(key);
  alarmTimer->loop();
  temp ->loop();
  printMainScreen();
}

void CoreMain::usePreset(int i) {
  if (i < 0 || i >= TimerPreset::PRESETS_COUNT)
    return;
  TimerPreset* p = TimerPreset::all[i];
  if (p != nullptr)
    alarmTimer->usePreset(p);
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
