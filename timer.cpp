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

char* Timer::getSecondsStr() {
  int sec = getSeconds();
  if (sec < 0)
    return " off";
  snprintf(txtBuffer, TXT_BUFFER_COUNT, "%04d", sec);
  return txtBuffer;

}

void Timer::off() {
  value = 0;
}