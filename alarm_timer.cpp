#include "alarm_timer.h"

AlarmTimer::AlarmTimer(Melody *melody, Melody *buzz) {
  //int*   dripTiming      = new int[4] {3, 33, 33+60, 33+60+90};
  //int    dripTimingCount = 4;
  playMelody = new ActionMelody(melody);
  playBuzz   = new ActionMelody(buzz);
  multiAlarm.alarmsCount = 6;
  multiAlarm.alarms = new Alarm[6] {
    Alarm(playMelody, 3  ),
    Alarm(playBuzz  , 23 ),
    Alarm(playMelody, 33 ),
    Alarm(playBuzz  , 83 ),
    Alarm(playMelody, 93 ),
    Alarm(playMelody, 183)
  };
}

AlarmTimer::~AlarmTimer() {
  //for (int i=0; i<multiAlarm.alarmsCount; i++) {
  //  delete(multiAlarm.alarms[i]);
  //}
  delete(multiAlarm.alarms);
  delete(playMelody);
  delete(playBuzz  );
}

void AlarmTimer::loop() {
  if (!isOn)
    return;
  int sec = timer.getSecondsTotal();
  multiAlarm.check(sec);
}

void AlarmTimer::startDrip() {
  timer.start();
  isOn = true;
}

void AlarmTimer::stop() {
  isOn = false;
}

int AlarmTimer::getSecondsTotal() {
  if (!isOn)
    return 0;
  return timer.getSecondsTotal();
}

char* AlarmTimer::toString() {
  return "drip";
}