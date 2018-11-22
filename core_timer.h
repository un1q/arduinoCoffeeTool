#ifndef CORE_TIMER_H_
#define CORE_TIMER_H_

#include "core.h"
#include "lcd.h"
#include "sensor_alarm.h"
#include "string_buffer.h"

class CoreTimer : public Core {
  private:
    Lcd::OneAlarm lcdOneAlarm;
    SensorAlarm   *alarm         = nullptr;
    unsigned long lastChangeTime = 0;
    char          *input         = "00:00";
    StringBuffer  remains        = StringBuffer(7);
  public:
    virtual ~CoreTimer();
    virtual int  update(char key);
    virtual void start();
  private:
    void printScreen();
    int  getValue();
    void destroyAlarm();
};

#endif