#include "measure_weight.h"

MeasureWeight::MeasureWeight(int DOUT, int CLK, float calibrationFactor, int CHK = -1) {
  this->calibrationFactor = calibrationFactor;
  scale = new HX711(DOUT, CLK);
  this->CHK = CHK;
  if (CHK != -1)
    pinMode(CHK, INPUT_PULLUP);
}

MeasureWeight::~MeasureWeight() {
  delete(scale);
}

void MeasureWeight::setup() {
  if (CHK != -1)
    pinMode(CHK, INPUT_PULLUP);
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
  return (CHK == -1 || digitalRead(CHK) == LOW ) && scale->is_ready();
}