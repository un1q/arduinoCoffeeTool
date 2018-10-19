#ifndef LCD_H_
#define LCD_H_

#include "timer.h";
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define TXT_BUFFER_COUNT 16

class Lcd {
  char txtBuffer [TXT_BUFFER_COUNT];
  LiquidCrystal_I2C* lcd;
  
  char* secToStr(int);
  char* tempToStr(int);
public:
  Lcd();
  ~Lcd();
  void init();
  void music();
  void printTimer(Timer *timer);
  void printTemp(int temp);
  void print(char*);
  void printChar(char);
  void setHeader(char* header);
  void clearLine(int lineNr);
};

#endif
