#ifndef MEASURE_WEIGHT_H_
#define MEASURE_WEIGHT_H_

#include "HX711.h"

class MeasureWeight {
    float calibrationFactor;
    HX711 *scale;
  public:
    MeasureWeight(int DOUT, int CLK, float calibrationFactor);
    ~MeasureWeight();
    void setup();
    void tare();
    int  get();
};

#endif