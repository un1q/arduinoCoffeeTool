#ifndef MEASURE_TIME_H_
#define MEASURE_TIME_H_

#include "sensor.h"

class MeasureTime : public Sensor {
    unsigned long time = 0ul;
  public:
    void start();
    void start(int initSeconds);
    void stop();
    int get(); //return time in seconds
    bool active();
};

#endif