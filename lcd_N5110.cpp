#include "lcd_N5110.h"

Lcd_N5110::Lcd_N5110() : Lcd_N5110(A1,A2,A3,A4,A5) {}

Lcd_N5110::Lcd_N5110(int pin_SCLK, int pin_DIN, int pin_DC, int pin_CS, int pin_RST) {
  display = new Adafruit_PCD8544(pin_SCLK, pin_DIN, pin_DC, pin_CS, pin_RST);
}

Lcd_N5110::~Lcd_N5110() {
  delete(display);
}

void Lcd_N5110::setup() {
  display->begin();
  display->setContrast(50);
  display->clearDisplay();
  display->setTextSize(1);
  display->setTextColor(BLACK,WHITE);
}

void Lcd_N5110::print(Lcd::Info *info) {
  print(POS_TEMP        , tempStringBuffer  .intToString(info->temp < -99 ? -99 : info->temp, "%03dC"));
  print(POS_WEIGHT      , weightStringBuffer.intToString(info->weight, "%03dg"));
  print(POS_TIMER       , timeStringBuffer  .secondsToString(info->time, 5));
  print(POS_ALARM_TEMP  , info->tempAlarm);
  print(POS_ALARM_WEIGHT, info->weightAlarm);
  print(POS_ALARM_TIMER , info->timeAlarm);
  display->display();
}

void Lcd_N5110::print(Lcd::Menu *menu) {
  char s[3];
  s[0]='F';
  s[2]='\0';
  for (int i=0; i<menu->size; i++) {
    int y = i*rowHeight;
    if (i == menu->selected) {
      print(0, y, ">>");
    } else if (i<=5) {
      s[1]=i+'1';
      print(0, y, s);
    }
    print(menuPadding, y, menu->options[i]);
  }
}

void Lcd_N5110::print(int positionIndex, char* text) {
  int* pos = positions[positionIndex];
  print(pos[0], pos[1], text);
}

void Lcd_N5110::print(int x, int y, char* text) {
  if (text == nullptr)
    return;
  display->setCursor(x, y);
  display->print(text);
  display->display();
}

void Lcd_N5110::clear() {
  display->clearDisplay();
}