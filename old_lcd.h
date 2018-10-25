/*
#ifndef LCD_H_
#define LCD_H_

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "timer.h";
#include "keyboard.h"
#include "core_timer.h"
#include "core_temp.h"

#define TXT_BUFFER_COUNT 17

class Lcd {
  char txtBuffer [TXT_BUFFER_COUNT];
  LiquidCrystal_I2C *lcd;
  CoreTimer         *timer;
  CoreTemp          *temp;
  Keyboard          *keyboard;
  
  char* secToStr(int);
  char* tempToStr(int);
public:
  Lcd();
  ~Lcd();
  void setup(CoreTimer*, CoreTemp*, Keyboard*);
  void loop();
  void music();
  void printTimer(Timer *timer);
  void printTemp(int temp);
  void print(char*);
  void printChar(char);
  void setHeader(char* header);
  void clearLine(int lineNr);
};

#endif
*/