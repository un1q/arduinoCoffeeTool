#include "alarm_timer.h"
#include "string_buffer.h"

#include <Arduino.h>

AlarmTimer::AlarmTimer(TimerPreset *preset, Action *alarmAction, Action *buzzAction) {
  this->alarmAction = alarmAction;
  this->buzzAction  = buzzAction ;
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
  int sec = 0;
  sec = measureTime.getSecondsTotal();
  if (multiAlarm != nullptr)
    multiAlarm->check(sec);
}

void AlarmTimer::start() {
  measureTime.start(startAt);
  if (multiAlarm != nullptr)
    multiAlarm->reset();
  on = true;
}

void AlarmTimer::stop() {
  on = false;
  measureTime.stop();
}

char* AlarmTimer::toString() {
  if (multiAlarm == nullptr)
    return "none ";
  if (!isOn())
    return name == nullptr ? "?????" : name;
  Alarm* alarm = multiAlarm->getNext(measureTime.getSecondsTotal());
  if (alarm == nullptr)
    return "null ";
  return stringBuffer.secondsToString(alarm->alarmValue, 5);
}

void AlarmTimer::usePreset(TimerPreset *timerPreset) {
  destroyMultiAlarm();
  if (timerPreset == nullptr)
    return;
  int alarmsCount  = timerPreset->alarmsCount;
  int buzzersCount = timerPreset->buzzersCount;
  multiAlarm = new MultiAlarm();
  multiAlarm->alarmsCount = buzzersCount + alarmsCount;
  multiAlarm->alarms = new AlarmAbstract*[multiAlarm->alarmsCount];
  for (int i=0; i<buzzersCount; i++) {
    multiAlarm->alarms[i] = new Alarm(buzzAction, timerPreset->buzzers[i]);
  }
  for (int i=0; i<alarmsCount; i++) {
    multiAlarm->alarms[buzzersCount + i] = new Alarm(alarmAction, timerPreset->alarms[i]);
  }
  name    = timerPreset->name;
  startAt = timerPreset->startAt;
}

void AlarmTimer::destroyMultiAlarm() {
  if (multiAlarm == nullptr)
    return;
  for (int i=0; i<multiAlarm->alarmsCount; i++) {
    delete(multiAlarm->alarms[i]);
  }
  delete(multiAlarm->alarms);
  delete(multiAlarm);
  multiAlarm = nullptr;
}