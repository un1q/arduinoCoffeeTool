#include "alarm.h"

#include <Arduino.h>

Alarm::Alarm(Action *alarmAction, int alarmValue, Mode mode) {
  this->alarmAction = alarmAction;
  this->alarmValue  = alarmValue;
  this->mode        = mode;
}

Alarm::~Alarm() {}

void Alarm::reset() {
  direction = 0;
}

bool Alarm::check(int value) {
  if (direction == 0) {
    direction = alarmValue - value;
    if (direction > 0)
      direction = 1;
    else if(direction < 0)
      direction = -1;
    return false;
  }
  if (direction * (alarmValue - value) <= 0) {
    int oldDirection = direction;
    direction = 0;
    if (alarmAction)
      alarmAction->doIt();
    switch (mode) {
      case crossing:     return true;
      case crossingUp:   return oldDirection > 0;
      case crossingDown: return oldDirection < 0;
    }
  }
  return false;
}

void Alarm::changeValue(int value) {
  alarmValue = value;
}