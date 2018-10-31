#include "alarm.h"

Alarm::Alarm(Action *alarmAction, int alarmValue) {
  this->alarmAction = alarmAction;
  this->alarmValue  = alarmValue;
}

bool Alarm::check(int value) {
  if (direction == 0) {
    direction = alarmValue - value;
    return false;
  }
  if (direction * (alarmValue - value) < 0) {
  //if ((direction > 0 && value > alarmValue) || (direction < 0 && value < alarmValue) {
    direction = 0;
    alarmAction->doIt();
    return true;
  }
  return false;
}

int Alarm::difference(int value) {
  return value - alarmValue;
}
