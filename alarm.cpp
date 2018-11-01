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
  //if ((direction > 0 && value >= alarmValue) || (direction < 0 && value <= alarmValue)) {
    //Serial.print("alarmValue:");
    //Serial.print(alarmValue);
    //Serial.print(" value:");
    //Serial.print(value);
    //Serial.print(" direction:");
    //Serial.println(direction);
    direction = 0;
    alarmAction->doIt();
    return true;
  }
  return false;
}

int Alarm::difference(int value) {
  return value - alarmValue;
}
