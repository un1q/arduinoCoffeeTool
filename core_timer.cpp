#include "core_timer.h"

CoreTimer::CoreTimer(Melody *melody, Melody *buzz):
  melody(melody), buzz(buzz)
{}

void CoreTimer::start() {
  lcd->setHeader("Timer");
}

void CoreTimer::loop(char key)  {
  static bool buzzed = false;
  if (key == 'D') {
    timer.setSeconds(dripTiming, dripTimingCount);
    buzzed = false;
  }
  int sec = timer.getSeconds();
  if (sec == 0) {
    lcd->music();
    melody->play();
    timer.nextAlarm();
    buzzed = false;
  } else if (!buzzed && sec>5 && sec <= 10) {
    lcd->music();
    buzz->play();
    buzzed = true;
  }
  lcd->printTimer(&timer);
  delay(50);
}
