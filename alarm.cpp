#include "alarm.h"

#include <Arduino.h>

Alarm::Alarm(Action *alarmAction, int alarmValue, Mode mode) {
  this->alarmAction = alarmAction;
  this->alarmValue  = alarmValue;
  this->mode        = mode;
  switch (mode) {
    case crossing:     direction =  0; return;
    case crossingUp:   direction =  1; return;
    case crossingDown: direction = -1; return;
  }

}

Alarm::~Alarm() {}

void Alarm::reset() {
  direction = 0;
  clicked = false;
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
    bool result = false;
    switch (mode) {
      case crossing:     result = true         ; break;
      case crossingUp:   result = direction > 0; break;
      case crossingDown: result = direction < 0; break;
    }
    direction = 0;
    if (result) {
      clicked = true;
      doIt();
    }
    return result;
  }
  return false;
}

void Alarm::changeValue(int value) {
  alarmValue = value;
}