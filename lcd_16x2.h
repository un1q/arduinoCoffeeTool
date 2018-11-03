#ifndef LCD_16X2_H_
#define LCD_16X2_H_

#include "lcd.h"
#include "string_buffer.h"

#include <LiquidCrystal_I2C.h>

typedef int* Position;

class Lcd_16x2 : public Lcd {
  private:
    LiquidCrystal_I2C *lcd;
    const static int startPosition = 3;
    int selectedPosition  = startPosition;
    int positions[8][2] = { //some important positions (x,y)
      {01,1},
      {06,1},
      {11,1},
      {01,0},
      {06,0},
      {11,0},
      {01,1},
      {10,1}
    };
    const int POS_TEMP          = 0; // position index of temperature
    const int POS_WEIGHT        = 1; // position index
    const int POS_TIMER         = 2; // position index
    const int POS_ALARM_TEMP    = 3; // position index
    const int POS_ALARM_WEIGHT  = 4; // position index
    const int POS_ALARM_TIMER   = 5; // position index
    const int POS_PRESET_OPTION = 6; // position index of preset option
    const int POS_BACK_OPTION   = 7; // position index
    StringBuffer tempStringBuffer  ;
    StringBuffer weightStringBuffer;
    StringBuffer timeStringBuffer  ;
  public:
    Lcd_16x2();
    ~Lcd_16x2();
    void print(Lcd::Info *info);
    void print(Lcd::Menu *menu);
    void setup();
  private:
    void clear();
    void print(int positionIndex, char* text);
    void print(Position position, char* text);
    void print(int x, int y, char* text);
};

#endif
