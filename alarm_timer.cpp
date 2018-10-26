#include "alarm_timer.h"

AlarmTimer::AlarmTimer(Melody *melody, Melody *buzz):
  melody(melody), buzz(buzz)
{}

void AlarmTimer::loop() {
  int sec = getSecondsTotal();
  if (sec == 0) {
    melody->play();
    timer.nextAlarm();
    buzzed = false;
  } else if (!buzzed && sec>5 && sec <= 10) {
    buzz->play();
    buzzed = true;
  }
}

int AlarmTimer::getSecondsTotal() {
  return timer.getSeconds();
}

void AlarmTimer::startDrip() {
  timer.setSeconds(dripTiming, dripTimingCount);
  buzzed = false;
}

void AlarmTimer::stop() {
  timer.off();
}

char* AlarmTimer::toString() {
  return "drip";
}