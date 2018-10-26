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
  print(position[0], position[1], text);
}

void Lcd::print(int x, int y, char* text) {
  lcd->setCursor(x, y);
  lcd->print(text);
}

void Lcd::print(int positionIndex, char* text) {
  print(positions[positionIndex], text);
}

void Lcd::clear() {
  lcd->setCursor(0,0);
  lcd->print("                ");
  lcd->setCursor(0,1);
  lcd->print("                ");
}

void Lcd::selectUp() {
  switch (selectedPosition) {
    case 3: setSelectedPosition(POS_PRESET_OPTION); break;
    case 4: setSelectedPosition(POS_PRESET_OPTION); break;
    case 5: setSelectedPosition(POS_BACK_OPTION)  ; break;
    case 6: setSelectedPosition(POS_ALARM_TEMP)   ; break;
    case 7: setSelectedPosition(POS_ALARM_TIMER)  ; break;
  }
}

void Lcd::selectDown() {
  selectUp();
}

void Lcd::selectLeft() {
  if (selectedPosition == 3)
    setSelectedPosition(5);
  else if (selectedPosition == 6)
    setSelectedPosition(7);
  else
    setSelectedPosition(selectedPosition-1);
}

void Lcd::selectRight() {
  if (selectedPosition == 5)
    setSelectedPosition(3);
  else if (selectedPosition == 7)
    setSelectedPosition(6);
  else
    setSelectedPosition(selectedPosition+1);
}

int  Lcd::getSelectedPosition() {
  return selectedPosition;
}

void Lcd::startSelection() {
  selectedPosition = startPosition;
}

void Lcd::setSelectedPosition(int newPosition) {
  Serial.print("newPosition :");
  Serial.println(newPosition);
  if (newPosition == selectedPosition)
    return;
  print(positions[selectedPosition][0]-1, positions[selectedPosition][1], " ");
  selectedPosition = newPosition;
  print(positions[selectedPosition][0]-1, positions[selectedPosition][1], ">");
}