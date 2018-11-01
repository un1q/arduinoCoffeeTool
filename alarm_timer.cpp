#include "alarm_timer.h"
#include "global_string_buffer.h"

AlarmTimer::AlarmTimer(Melody *melody, Melody *buzz) {
  //int*   dripTiming      = new int[4] {3, 33, 33+60, 33+60+90};
  //int    dripTimingCount = 4;
  playMelody = new ActionMelody(melody);
  playBuzz   = new ActionMelody(buzz);
  multiAlarm.alarmsCount = 6;
  multiAlarm.alarms = new AlarmAbstract*[6] {
    new Alarm(playMelody, 0  ),
    new Alarm(playBuzz  , 20 ),
    new Alarm(playMelody, 30 ),
    new Alarm(playBuzz  , 80 ),
    new Alarm(playMelody, 90 ),
    new Alarm(playMelody, 180)
  };
}

AlarmTimer::~AlarmTimer() {
  for (int i=0; i<multiAlarm.alarmsCount; i++) {
    delete(multiAlarm.alarms[i]);
  }
  delete(multiAlarm.alarms);
  delete(playMelody);
  delete(playBuzz  );
}

void AlarmTimer::loop() {
  if (!isOn)
    return;
  int sec = measureTime.getSecondsTotal();
  multiAlarm.check(sec);
}

void AlarmTimer::startDrip() {
  measureTime.start(-3);
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