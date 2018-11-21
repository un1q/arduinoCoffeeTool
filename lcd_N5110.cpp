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
  unsigned long time = millis();
  if (time > lastRefreshTime && time - lastRefreshTime < 200)
    return;
  lastRefreshTime = time;
  display->clearDisplay();
  print(POS_TEMP        , tempStringBuffer  .tempToString(info->temp), false);
  print(POS_WEIGHT      , weightStringBuffer.weightToString(info->weight), false);
  print(POS_TIMER       , timeStringBuffer  .secondsToString(info->time, 5), false);
  int alarmY = positions[POS_ALARM][1];
  display->writeFastHLine(0, alarmY-4, 96, BLACK);
  display->writeFastHLine(0, alarmY+8+2, 96, BLACK);
  printCentered(alarmY, info->alarmDesc, false);
  display->setTextColor(WHITE,BLACK);
  print(POS_STEP        , info->step, false);
  display->setTextColor(BLACK,WHITE);
  print(POS_NEXT_STEP   , info->nextStep, false);
  display->display();
}

void Lcd_N5110::print(Lcd::Menu *menu) {
  char s[3];
  s[0]='F';
  s[2]='\0';
  for (int i=0; i<menu->size; i++) {
    int y = i*rowHeight;
    if (i == menu->selected) {
      print(0, y, ">>", false);
    } else if (i<=5) {
      s[1]=i+'1';
      print(0, y, s, false);
    }
    print(menuPadding, y, menu->options[i], false);
  }
  display->display();
}

void Lcd_N5110::print(int positionIndex, const char* text, bool refresh) {
  int* pos = positions[positionIndex];
  print(pos[0], pos[1], text, refresh);
}

void Lcd_N5110::print(int x, int y, const char* text, bool refresh) {
  if (text == nullptr)
    return;
  display->setCursor(x, y);
  display->print(text);
  if (refresh)
    display->display();
}

void Lcd_N5110::printCentered(int y, const char* text, bool refresh) {
  int x = (14-strlen(text)) * 3;
  print(x, y, text, refresh);
}

void Lcd_N5110::clear() {
  display->clearDisplay();
}