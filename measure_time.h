#ifndef MEASURE_TIME_H_
#define MEASURE_TIME_H_

class MeasureTime {
    unsigned long time = 0ul;
  public:
    void start();
    void start(int initSeconds);
    void stop();
    int getSecondsTotal();
};

#endif