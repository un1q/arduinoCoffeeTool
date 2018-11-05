#include "measure_time.h"

#include <Arduino.h>

void MeasureTime::start() {
  time = millis();
}

void MeasureTime::start(int initSeconds) {
  time = millis() - initSeconds * 1000ul;
}

void MeasureTime::stop() {
  time = 0;
}

int MeasureTime::getSecondsTotal() {
  if (time == 0)
    return 0;
  unsigned long now = millis();
  if (now > time)
    return (int)((now - time)/1000ul);
  else
    return -(int)((time - now)/1000ul);
}