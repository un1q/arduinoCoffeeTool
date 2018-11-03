#include "lcd_16x2.h"

Lcd_16x2::Lcd_16x2() {
  lcd = new LiquidCrystal_I2C(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
}

Lcd_16x2::~Lcd_16x2() {
  delete(lcd);
}

void Lcd_16x2::setup() {
  lcd->begin(16,2);
  lcd->backlight();
  lcd->clear();
}

void Lcd_16x2::print(Position position, char* text) {
  print(position[0], position[1], text);
}

void Lcd_16x2::print(int x, int y, char* text) {
  lcd->setCursor(x, y);
  lcd->print(text == nullptr ? "null" : text);
}

void Lcd_16x2::print(int positionIndex, char* text) {
  print(positions[positionIndex], text);
}

void Lcd_16x2::clear() {
  lcd->setCursor(0,0);
  lcd->print("                ");
  lcd->setCursor(0,1);
  lcd->print("                ");
}

void Lcd_16x2::print(Lcd::Info *info) {
  //lcd->clear();
  print(POS_TEMP        , tempStringBuffer  .intToString(info->temp < -99 ? -99 : info->temp, "%03dC"));
  print(POS_WEIGHT      , weightStringBuffer.intToString(info->weight, "%03dg"));
  print(POS_TIMER       , timeStringBuffer  .secondsToString(info->time, 5));
  print(POS_ALARM_TEMP  , info->tempAlarm);
  print(POS_ALARM_WEIGHT, info->weightAlarm);
  print(POS_ALARM_TIMER , info->timeAlarm);
}

void Lcd_16x2::print(Lcd::Menu *menu) {
  lcd->clear();
  print(0, 0, "MENU IS");
  print(0, 1, "NOT IMPLEMENTED");
}
