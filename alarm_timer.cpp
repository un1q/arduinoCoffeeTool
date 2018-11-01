#include "alarm_timer.h"
#include "global_string_buffer.h"

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
  delete(multiAlarm.alarms);
  delete(playMelody);
  delete(playBuzz  );
}

void AlarmTimer::loop() {
  if (!isOn)
    return;
  int sec = measureTime.getSecondsTotal();
  if (sec > 0)
    multiAlarm.check(sec);
}

void AlarmTimer::startDrip() {
  measureTime.start();
  multiAlarm.reset();
  isOn = true;
}

void AlarmTimer::stop() {
  isOn = false;
}

int AlarmTimer::getSecondsTotal() {
  if (!isOn)
    return 0;
  return measureTime.getSecondsTotal();
}

char* AlarmTimer::toString() {
  if (!isOn)
    return "drip";
  //return GlobalStringBuffer::intToString(multiAlarm.difference(measureTime.getSecondsTotal()), "% 4d");
  Alarm* alarm = multiAlarm.getNext(measureTime.getSecondsTotal());
  if (alarm == nullptr)
    return "null";
  return GlobalStringBuffer::secondsToString(alarm->alarmValue);
}