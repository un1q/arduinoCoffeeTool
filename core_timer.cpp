#include "core_timer.h"
#include "globals.h"

CoreTimer::~CoreTimer() {
  if (alarm)
    delete(alarm);
  alarm = nullptr;
}

void CoreTimer::start() {
  keyboard.setShiftMode(shift_off);
}

int  CoreTimer::update(char key) {
  switch (key) {
    case k_ENTER:
      measureTime.start();
      alarm = new SensorAlarm(&alarmAction, &measureTime, getValue(), 10, Alarm::crossingUp);
      timerStartMelody.play();
      break;
    case k_LEFT: 
      return Core::MAIN_MENU;
    default:
      if (key >= '0' && key <= '9') {
        input[0]=input[1];
        input[1]=input[3];
        input[3]=input[4];
        input[4]=key;
        if ( alarm )
          alarm->changeValue(getValue());
        lastChangeTime = millis();
      }
      break;
  }
  printScreen();
  if ( alarm && (millis() - lastChangeTime > 1000) )
    alarm->check();
  return -1;
}

int  CoreTimer::getValue() {
  return
    (input[0]-'0')*600+
    (input[1]-'0')*60 +
    (input[3]-'0')*10 +
    (input[4]-'0');
}

void CoreTimer::printScreen() {
  lcdOneAlarm.temp       = measureTemp.get();
  lcdOneAlarm.time       = measureTime.get();
  lcdOneAlarm.weight     = measureWeight.get();
  lcdOneAlarm.bigText    = alarm ? remains.secondsToString(-alarm->remains()) : nullptr;
  lcdOneAlarm.normalText = input;
  lcd->print(&lcdOneAlarm);
}