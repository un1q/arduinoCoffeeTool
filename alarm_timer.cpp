#include "alarm_timer.h"
#include "string_buffer.h"

#include <Arduino.h>

AlarmTimer::AlarmTimer(MeasureTime *measureTime, TimerPreset *preset, Action *alarmAction, Action *buzzAction) {
  this->alarmAction = alarmAction;
  this->buzzAction  = buzzAction ;
  this->measureTime = measureTime;
  this->multiAlarm  = nullptr;
  usePreset(preset);
}

AlarmTimer::~AlarmTimer() {
  destroyMultiAlarm();
}

bool AlarmTimer::isOn() {
  return on && multiAlarm != nullptr;
}

void AlarmTimer::loop() {
  if (!isOn())
    return;
  int sec = measureTime->getSecondsTotal();
  multiAlarm->check(sec);
}

void AlarmTimer::start() {
  measureTime->start(-3);
  multiAlarm->reset();
  on = true;
}

void AlarmTimer::stop() {
  on = false;
  measureTime->stop();
}

char* AlarmTimer::toString() {
  if (multiAlarm == nullptr)
    return "none";
  if (!isOn())
    return "drip";
  Alarm* alarm = multiAlarm->getNext(measureTime->getSecondsTotal());
  if (alarm == nullptr)
    return "drip";
  return stringBuffer.secondsToString(alarm->alarmValue);
}

void AlarmTimer::usePreset(TimerPreset *timerPreset) {
  int alarmsCount  = timerPreset->alarmsCount;
  int buzzersCount = timerPreset->buzzersCount;
  destroyMultiAlarm();
  multiAlarm = new MultiAlarm();
  multiAlarm->alarmsCount = buzzersCount + alarmsCount;
  multiAlarm->alarms = new AlarmAbstract*[multiAlarm->alarmsCount];
  for (int i=0; i<buzzersCount; i++) {
    multiAlarm->alarms[i] = new Alarm(buzzAction, timerPreset->buzzers[i]);
  }
  for (int i=0; i<alarmsCount; i++) {
    multiAlarm->alarms[buzzersCount + i] = new Alarm(alarmAction, timerPreset->alarms[i]);
  }
}

void AlarmTimer::destroyMultiAlarm() {
  if (multiAlarm == nullptr)
    return;
  for (int i=0; i<multiAlarm->alarmsCount; i++) {
    delete(multiAlarm->alarms[i]);
  }
  delete(multiAlarm->alarms);
  multiAlarm = nullptr;

}