#include "timer.h"

#include <Arduino.h>

void Timer::setSeconds(int sec) {
  value = millis() + sec * 1000ul;
}

int Timer::getSeconds() {
  if (value == 0)
    return -1;
  unsigned long time = millis();
  if (time > value)
    return 0;
  return (int)((value - time)/1000ul);
}

void Timer::off() {
  value = 0;
}