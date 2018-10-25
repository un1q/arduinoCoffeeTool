#include "lcd.h"

Lcd::Lcd() {
  lcd = new LiquidCrystal_I2C(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
}

Lcd::~Lcd() {
  delete(lcd);
}

void Lcd::setup() {
  lcd->begin(16,2);
  lcd->backlight();
  lcd->clear();
}

void Lcd::print(Position position, char* text) {
  lcd->setCursor(position[0], position[1]);
  lcd->print(text);
}

void Lcd::clear() {
  lcd->setCursor(0,0);
  lcd->print("                ");
  lcd->setCursor(0,1);
  lcd->print("                ");
}