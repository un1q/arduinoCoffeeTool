#include "alarm.h"

#include <Arduino.h>

Alarm::Alarm(Action *alarmAction, int alarmValue) {
  this->alarmAction = alarmAction;
  this->alarmValue  = alarmValue;
}

void Alarm::reset() {
  direction = 0;
}

bool Alarm::check(int value) {
  if (direction == 0) {
    direction = (alarmValue - value > 0);
    if (direction > 0)
      direction = 1;
    else if(direction < 0)
      direction = -1;
    return false;
  }
  if (direction * (alarmValue - value) <= 0) {
    direction = 0;
    alarmAction->doIt();
    return true;
  }
  return false;
}

int Alarm::remains(int value) {
  return value - alarmValue;
}

Alarm::~Alarm() {}