#ifndef LCD_H_
#define LCD_H_

#include <LiquidCrystal_I2C.h>

typedef int* Position;

class Lcd {
    LiquidCrystal_I2C *lcd;
  public:
    int POS_TEMP         [2] = {00, 1};
    int POS_WEIGHT       [2] = {05, 1};
    int POS_TIMER        [2] = {11, 1};
    int POS_ALARM_TEMP   [2] = {00, 0};
    int POS_ALARM_WEIGHT [2] = {06, 0};
    int POS_ALARM_TIMER  [2] = {12, 0};
    
    Lcd();
    ~Lcd();
    void setup();
    void clear();
    void print(Position position, char* text);
};

#endif
