#include "core_timer.h"

CoreTimer::CoreTimer(Melody *melody, Melody *buzz):
  melody(melody), buzz(buzz)
{}

void CoreTimer::loop() {
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

int CoreTimer::getSecondsTotal() {
  return timer.getSeconds();
}

void CoreTimer::startDrip() {
  timer.setSeconds(dripTiming, dripTimingCount);
  buzzed = false;
}

void CoreTimer::stop() {
  timer.off();
}