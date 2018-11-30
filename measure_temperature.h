#ifndef MEASURE_TEMPERATURE_H_
#define MEASURE_TEMPERATURE_H_

// temperature sensor
#include "sensor.h"

#include <OneWire.h>
#include <DallasTemperature.h>


#define TEMP_PIN 12
//(a 4.7K resistor is necessary)

class MeasureTemperature : public Sensor {
    OneWire           *oneWire;
    DallasTemperature *sensors;
    int temp;
  public:
    MeasureTemperature();
    void loop();
    int  get();
    bool active();
};


#endif