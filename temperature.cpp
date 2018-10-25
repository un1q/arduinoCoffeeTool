#include "temperature.h"

Temperature::Temperature() {
  oneWire = new OneWire(TEMP_PIN);
  sensors = new DallasTemperature(oneWire);
}

void Temperature::loop() {
  sensors->requestTemperatures();
  temp = sensors->getTempCByIndex(0);
}

int Temperature::getTemp() {
  return temp;
}