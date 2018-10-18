#include "lcd.h"

Lcd::Lcd() {
  lcd = new LiquidCrystal_I2C(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
}

Lcd::~Lcd() {
  delete(lcd);
}

void Lcd::init() {
  lcd->begin(16,2);
  lcd->backlight();
  lcd->setCursor(0,0);
  lcd->print("Timer");
}

void Lcd::music() {
  lcd->setCursor(0,1);
  lcd->print("!!!!");
}

char* Lcd::secToStr(int sec) {
  if (sec < 0)
    return " off";
  snprintf(txtBuffer, TXT_BUFFER_COUNT, "%04d", sec);
  return txtBuffer;
}

void Lcd::timer(Timer *timer) {
  int sec = timer->getSeconds();
  lcd->setCursor(0,1);
  lcd->print(secToStr(sec));
}