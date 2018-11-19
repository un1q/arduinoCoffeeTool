#ifndef SENSOR_ALARM_H_
#define SENSOR_ALARM_H_

#include "alarm.h"
#include "sensor.h"
#include "action.h"

//TODO: timeoutIfNoSensor

class SensorAlarm : public Alarm {
    Alarm  *buzzAlarm = nullptr;
    Sensor *sensor    = nullptr;
  public:
    SensorAlarm(Action *alarmAction, Action *buzzAction, Sensor *sensor, int value, int buzz, Alarm::Mode mode = Alarm::crossing);
    ~SensorAlarm();
    void reset();
    bool check();
    bool activeSensor();
};

#endif