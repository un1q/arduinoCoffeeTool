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
  //display->setRotation(1);
}

#include <Arduino.h>

void Lcd_N5110::print(Lcd::Info *info) {
  Serial.println("TEST!");
  //display->clearDisplay();
  //display->setCursor(0,0);
  print(POS_TEMP        , tempStringBuffer  .intToString(info->temp < -99 ? -99 : info->temp, "%03dC"));
  print(POS_WEIGHT      , weightStringBuffer.intToString(info->weight, "%03dg"));
  print(POS_TIMER       , timeStringBuffer  .secondsToString(info->time, 5));
  print(POS_ALARM_TEMP  , info->tempAlarm);
  print(POS_ALARM_WEIGHT, info->weightAlarm);
  print(POS_ALARM_TIMER , info->timeAlarm);
  display->display();
}

void Lcd_N5110::print(Lcd::Menu *menu) {}

void Lcd_N5110::print(int positionIndex, char* text) {
  int* pos = positions[positionIndex];
  display->setCursor(pos[0], pos[1]);
  display->print(text);
  display->display();
}
