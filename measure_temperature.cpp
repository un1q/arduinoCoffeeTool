#include "measure_temperature.h"

MeasureTemperature::MeasureTemperature() {
  oneWire = new OneWire(TEMP_PIN);
  sensors = new DallasTemperature(oneWire);
}

void MeasureTemperature::loop() {
  sensors->requestTemperatures();
  temp = sensors->getTempCByIndex(0);
}

int MeasureTemperature::get() {
  return temp;
}

bool MeasureTemperature::active() {
  return get() > -99;
}