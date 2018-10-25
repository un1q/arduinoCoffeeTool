#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_

#include <OneWire.h>
#include <DallasTemperature.h>

#define TEMP_PIN 10
//(a 4.7K resistor is necessary)

class Temperature {
    OneWire           *oneWire;
    DallasTemperature *sensors;
    int temp;
  public:
    Temperature();
    void loop();
    int  getTemp();
};


#endif