#ifndef MEASURE_TEMPERATURE_H_
#define MEASURE_TEMPERATURE_H_

// temperature sensor

#include <OneWire.h>
#include <DallasTemperature.h>

#define TEMP_PIN 10
//(a 4.7K resistor is necessary)

class MeasureTemperature {
    OneWire           *oneWire;
    DallasTemperature *sensors;
    int temp;
  public:
    MeasureTemperature();
    void loop();
    int  getTemp();
};


#endif