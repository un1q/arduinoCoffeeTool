#ifndef SENSOR_H_
#define SENSOR_H_

class Sensor {
  public:
    virtual int  get()    = 0;
    virtual bool active() = 0;
};

#endif