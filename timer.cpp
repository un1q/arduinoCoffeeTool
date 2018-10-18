#include "timer.h"

#include <Arduino.h>

void Timer::setSeconds(int sec) {
  setSeconds(&sec, 1);
}

void Timer::setSeconds(int* sec, int count) {
  off(); //destroy old alarms
  alarmsCount  = count;
  alarms       = new unsigned long[count];
  currentAlarm = 0;
  unsigned long now = millis();
  for (int i=0; i < count; i++) {
    alarms[i] = now + sec[i] * 1000ul;
  }
}

int Timer::getSeconds() {
  if (!isOn())
    return -1;
  unsigned long now = millis();
  unsigned long alarmTime = alarms[currentAlarm];
  if (now > alarmTime)
    return 0;
  return (int)((alarmTime - now)/1000ul);
}

bool Timer::nextAlarm() {
  if (++currentAlarm >= alarmsCount) {
    off();
    return false;
  }
  return true;
}

bool Timer::isOn() {
  return currentAlarm >= 0;
}

void Timer::off() {
  if (alarmsCount > 0)
    delete(alarms);
  alarmsCount = 0;
  currentAlarm = -1;
}