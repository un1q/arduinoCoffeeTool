#ifndef CORE_TEMP_H_
#define CORE_TEMP_H_

#include "core.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define TEMP_PIN 10
//(a 4.7K resistor is necessary)

class CoreTemp : public Core {
    OneWire           *oneWire;
    DallasTemperature *sensors;
  public:
    CoreTemp();
    void loop(char key);
    void start();
};

#endif