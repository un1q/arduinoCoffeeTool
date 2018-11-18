#ifndef MEASURE_WEIGHT_H_
#define MEASURE_WEIGHT_H_

#include "sensor.h"
#include "HX711.h"

class MeasureWeight : public Sensor {
    float calibrationFactor;
    HX711 *scale;
  public:
    MeasureWeight(int DOUT, int CLK, float calibrationFactor);
    ~MeasureWeight();
    void setup();
    void tare();
    int  get()    override;
    bool active() override;
};

#endif