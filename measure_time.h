#ifndef MEASURE_TIME_H_
#define MEASURE_TIME_H_

class MeasureTime {
    unsigned long time;
  public:
    void start();
    void start(int initSeconds);
    int getSecondsTotal();
};

#endif