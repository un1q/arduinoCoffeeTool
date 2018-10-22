#include "core_temp.h"

CoreTemp::CoreTemp() {
  oneWire = new OneWire(TEMP_PIN);
  sensors = new DallasTemperature(oneWire);
}

void CoreTemp::loop() {
  sensors->requestTemperatures();
  temp = sensors->getTempCByIndex(0);
}
