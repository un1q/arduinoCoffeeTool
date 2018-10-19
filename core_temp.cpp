#include "core_temp.h"

CoreTemp::CoreTemp() {
  oneWire = new OneWire(TEMP_PIN);
  sensors = new DallasTemperature(oneWire);
}

void CoreTemp::start() {
  lcd->setHeader("Temperature");
}

void CoreTemp::loop(char key) {
  sensors->requestTemperatures();
  int temp = sensors->getTempCByIndex(0);
  lcd->printTemp(temp);
  delay(50);
}
