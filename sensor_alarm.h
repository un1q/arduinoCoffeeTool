#ifndef SENSOR_ALARM_H_
#define SENSOR_ALARM_H_

#include "alarm.h"
#include "sensor.h"
#include "action.h"

//TODO: timeoutIfNoSensor

class SensorAlarm : public Alarm {
  private:
    static unsigned long nextBuzz;
  private:
    int    buzzMargin = 0;
    Sensor *sensor    = nullptr;
  public:
    SensorAlarm(Action *alarmAction, Sensor *sensor, int value, int buzzMargin, Alarm::Mode mode = Alarm::crossing);
    ~SensorAlarm();
    void reset();
    bool check();
    bool activeSensor();
    int  remains();
};

#endif