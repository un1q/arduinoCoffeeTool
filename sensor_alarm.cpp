#include "sensor_alarm.h"

#include "melody.h"
#include "pitches.h"
#include <Arduino.h>

static unsigned long SensorAlarm::nextBuzz = 0ul;

SensorAlarm::SensorAlarm(Action *alarmAction, Sensor *sensor, int value, int buzzMargin, Alarm::Mode mode) 
: Alarm(alarmAction, value, mode) {
  this->sensor = sensor;
  this->buzzMargin = buzzMargin;
}

SensorAlarm::~SensorAlarm() {
}

void SensorAlarm::reset() {
  Alarm::reset();
}

#define BUZZ_DUR_MAX    2000
#define BUZZ_DUR_MIN    100
bool SensorAlarm::check() {
  if (!sensor || !sensor->active()) 
    return false;
  int value = sensor->get();
  if (Alarm::check(value))
    return true;
  if (buzzMargin > 0 && abs(alarmValue-value) <= buzzMargin) {
    if ((mode == Alarm::crossingUp && alarmValue <= value ) || (mode == Alarm::crossingDown && alarmValue >= value ))
      return;
    unsigned long now = millis();
    if (now < SensorAlarm::nextBuzz)
      return;
    int d = buzzMargin - abs(alarmValue-value);
    int freq = NOTE_A3;
    Melody::playTone(freq, 100);
    SensorAlarm::nextBuzz = now + (BUZZ_DUR_MAX - ((BUZZ_DUR_MAX-BUZZ_DUR_MIN) / buzzMargin) * d);
  }
  return false;
}

bool SensorAlarm::activeSensor() {
  return sensor && sensor->active();
}

int  SensorAlarm::remains() {
  if (!sensor || !sensor->active()) 
    return 0;
  return alarmValue - sensor->get();

}