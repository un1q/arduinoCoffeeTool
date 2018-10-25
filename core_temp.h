#ifndef CORE_TEMP_H_
#define CORE_TEMP_H_

#include <OneWire.h>
#include <DallasTemperature.h>

#define TEMP_PIN 10
//(a 4.7K resistor is necessary)

class CoreTemp {
    OneWire           *oneWire;
    DallasTemperature *sensors;
    int temp;
  public:
    CoreTemp();
    void loop();
    int  getTemp();
};


#endif