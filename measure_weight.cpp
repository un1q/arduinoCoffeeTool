#include "measure_weight.h"

MeasureWeight::MeasureWeight(int DOUT, int CLK, float calibrationFactor) {
  this->calibrationFactor = calibrationFactor;
  scale = new HX711(DOUT, CLK);
}

MeasureWeight::~MeasureWeight() {
  delete(scale);
}

void MeasureWeight::setup() {
  scale->set_scale(calibrationFactor);
  scale->tare();
}

void MeasureWeight::tare() {
  scale->tare();
}

int  MeasureWeight::get() {
  float weight = scale->get_units();
  return (int)(weight+0.5); //round
}

bool MeasureWeight::active() {
  return false;
}