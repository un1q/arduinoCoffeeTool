#include "measure_time.h"

#include <Arduino.h>

void MeasureTime::start() {
  time = millis();
}

int MeasureTime::getSecondsTotal() {
  if (time == 0)
    return 0;
  unsigned long now = millis();
  return (int)((now - time)/1000ul);
}