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
    unsigned long lastRefreshTime = 0;
    int positions[8][2] = { //some important positions (x,y)
      { 0, 0},
      { 0, 9},
      { 0,18},
      {48, 0},
      {48, 9},
      {48,18},
      {0 ,27},
      {0 ,36}
    };
    const int POS_TEMP          = 0; // position index of temperature
    const int POS_WEIGHT        = 1; // position index
    const int POS_TIMER         = 2; // position index
    const int POS_ALARM_TEMP    = 3; // position index
    const int POS_ALARM_WEIGHT  = 4; // position index
    const int POS_ALARM_TIMER   = 5; // position index
    const int POS_STEP          = 6; // position index
    const int POS_NEXT_STEP     = 7; // position index
    const int rowHeight         = 8;
    const int menuPadding       = 16;
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
    void clear();
  private:
    void print(int positionIndex, char* text, bool refresh);
    void print(int x, int y, char* text, bool refresh);
};

#endif