#ifndef LCD_N5110_H_
#define LCD_N5110_H_

#include "lcd.h"
#include "string_buffer.h"

//default pins:
// pin A1 - Serial clock out (SCLK)
// pin A2 - Serial data out (DIN)
// pin A3 - Data/Command select (D/C)
// pin A4 - LCD chip select (CS)
// pin A5 - reset (RST)


#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

class Lcd_N5110 : public Lcd {
    int positions[6][2] = { //some important positions (x,y)
      {00,01},
      {00,15},
      {00,30},
      {48,00},
      {48,15},
      {48,30}
    };
    const int POS_TEMP          = 0; // position index of temperature
    const int POS_WEIGHT        = 1; // position index
    const int POS_TIMER         = 2; // position index
    const int POS_ALARM_TEMP    = 3; // position index
    const int POS_ALARM_WEIGHT  = 4; // position index
    const int POS_ALARM_TIMER   = 5; // position index
    StringBuffer tempStringBuffer  ;
    StringBuffer weightStringBuffer;
    StringBuffer timeStringBuffer  ;
    Adafruit_PCD8544 *display;
  public:
    Lcd_N5110();
    Lcd_N5110(int SCLK, int DIN, int DC, int CS, int RST);
    ~Lcd_N5110();
    void print(Lcd::Info *info);
    void print(Lcd::Menu *menu);
    void setup();
  private:
    void print(int positionIndex, char* text);
};

#endif