#ifndef MEASURE_WEIGHT_H_
#define MEASURE_WEIGHT_H_

#include "sensor.h"
#include "HX711.h"

class MeasureWeight : public Sensor {
    float calibrationFactor;
    HX711 *scale;
    int   CHK;
  public:
    MeasureWeight(int DOUT, int CLK, float calibrationFactor, int CHK = -1); //DOUT and CLS are PINS on scale, CHK is PIN used to check if scale is connected - it should be connected to GND only if scale is connected
    ~MeasureWeight();
    void setup();
    void tare();
    int  get()    override;
    bool active() override;
};

#endif