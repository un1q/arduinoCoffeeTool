#include "alarm_timer.h"
#include "string_buffer.h"

AlarmTimer::AlarmTimer(MeasureTime *measureTime, Melody *melody, Melody *buzz) {
  //int*   dripTiming      = new int[4] {3, 33, 33+60, 33+60+90};
  //int    dripTimingCount = 4;
  this->measureTime = measureTime;
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
  int sec = measureTime->getSecondsTotal();
  multiAlarm.check(sec);
}

void AlarmTimer::startDrip() {
  measureTime->start(-3);
  multiAlarm.reset();
  isOn = true;
}

void AlarmTimer::stop() {
  isOn = false;
}

char* AlarmTimer::toString() {
  if (!isOn)
    return "drip";
  Alarm* alarm = multiAlarm.getNext(measureTime->getSecondsTotal());
  if (alarm == nullptr)
    return "drip";
  return stringBuffer.secondsToString(alarm->alarmValue);
}