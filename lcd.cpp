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
}

void Lcd::music() {
  lcd->setCursor(0,1);
  lcd->print("!!!!");
}

char* Lcd::secToStr(int sec) {
  if (sec < 0)
    return " off";
  snprintf(txtBuffer, TXT_BUFFER_COUNT, "%04d            ", sec);
  return txtBuffer;
}

char* Lcd::tempToStr(int temp) {
  snprintf(txtBuffer, TXT_BUFFER_COUNT, "%03d C           ", temp);
  return txtBuffer;
}

void Lcd::setHeader(char* header) {
  clearLine(1);
  clearLine(0);
  lcd->print(header);
}

void Lcd::printTimer(Timer *timer) {
  int sec = timer->getSeconds();
  lcd->setCursor(0,1);
  lcd->print(secToStr(sec));
}

void Lcd::printTemp(int temp) {
  lcd->setCursor(0,1);
  lcd->print(tempToStr(temp));
}

void Lcd::print(char* txt) {
  clearLine(1);
  lcd->print(txt);
}

void Lcd::printChar(char c) {
  clearLine(1);
  lcd->print(c);

}

void Lcd::clearLine(int lineNr) {
  lcd->setCursor(0,lineNr);
  lcd->print("                ");
  lcd->setCursor(0,lineNr);
}