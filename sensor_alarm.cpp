#include "sensor_alarm.h"

#include <Arduino.h>

SensorAlarm::SensorAlarm(Action *alarmAction, Action *buzzAction, Sensor *sensor, int value, int buzzValue, Alarm::Mode mode) 
: Alarm(alarmAction, value, mode) {
  this->sensor = sensor;
  if (buzzAction)
    buzzAlarm =  new Alarm(buzzAction, buzzValue, mode);
}

SensorAlarm::~SensorAlarm() {
  if (buzzAlarm) {
    delete(buzzAlarm);
  }
}

void SensorAlarm::reset() {
  if (buzzAlarm)
    buzzAlarm->reset();
  Alarm::reset();
}

bool SensorAlarm::check() {
  if (!sensor || !sensor->active()) 
    return false;
  int value = sensor->get();
  if (buzzAlarm)
    buzzAlarm->check(value);
  return Alarm::check(value);
}

bool SensorAlarm::activeSensor() {
  return sensor && sensor->active();
}