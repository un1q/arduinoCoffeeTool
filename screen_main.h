#ifndef SCREEN_MAIN_H_
#define SCREEN_MAIN_H_

#include <LiquidCrystal_I2C.h>
#include "Lcd.h"

class ScreenMain {
    const static int txtBufferSize = 8;
    char txtBuffer[txtBufferSize];
    Lcd  *lcd;
  public:
    ScreenMain(Lcd *lcd);
    void start();
    void printTemp(int   temp);
    void printTemp(char* temp);
    void printWeight(int   weight);
    void printWeight(char* weight);
    void printTimer(int   time);
    void printTimer(char* time);
    void printAlarmTemp(int   temp);
    void printAlarmTemp(char* temp);
    void printAlarmWeight(int   weight);
    void printAlarmWeight(char* weight);
    void printAlarmTimer(int   time);
    void printAlarmTimer(char* time);
};

#endif
