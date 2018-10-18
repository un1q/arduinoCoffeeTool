#ifndef LCD_H_
#define LCD_H_

#include "timer.h";
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define TXT_BUFFER_COUNT 8

class Lcd {
  char txtBuffer [TXT_BUFFER_COUNT];
  LiquidCrystal_I2C* lcd;
  
  char* secToStr(int);
public:
  Lcd();
  ~Lcd();
  void init();
  void music();
  void timer(Timer *timer);
  void printChar(char);
};

#endif
