#include "screen_main.h"

ScreenMain::ScreenMain(Lcd *lcd) {
  this->lcd = lcd;
}

void ScreenMain::start() {
  lcd->clear();
}

void ScreenMain::printTemp(int   temp) {
  if (temp < -100)
    temp = -99;
  snprintf(txtBuffer, txtBufferSize, "%03dC", temp);
  printTemp(txtBuffer);
}

void ScreenMain::printTemp(char* temp) {
  lcd->print(lcd->POS_TEMP, temp);
}

void ScreenMain::printWeight(int   weight) {
}

void ScreenMain::printWeight(char* weight) {
  lcd->print(lcd->POS_WEIGHT, weight);
}

void ScreenMain::printTimer(int   secTotal) {
  int sec = 0;
  int min = 0;
  if (secTotal > 0) {
    sec = secTotal % 60;
    min = secTotal / 60;
  }
  snprintf(txtBuffer, txtBufferSize,"% 2d:%02d",min,sec);
  printTimer(txtBuffer);
}

void ScreenMain::printTimer(char* time) {
  lcd->print(lcd->POS_TIMER, time);
}

void ScreenMain::printAlarmTemp(int   temp) {
}

void ScreenMain::printAlarmTemp(char* temp) {
  lcd->print(lcd->POS_ALARM_TEMP, temp);
}

void ScreenMain::printAlarmWeight(int   weight) {
}

void ScreenMain::printAlarmWeight(char* weight) {
  lcd->print(lcd->POS_ALARM_WEIGHT, weight);
}

void ScreenMain::printAlarmTimer(int   time) {
}

void ScreenMain::printAlarmTimer(char* time) {
  lcd->print(lcd->POS_ALARM_TIMER, time);
}

void ScreenMain::printPresetOption() {
  lcd->print(lcd->POS_PRESET_OPTION, "preset");
}

void ScreenMain::printBackOption() {
  lcd->print(lcd->POS_BACK_OPTION, "back");
}

void ScreenMain::selectUp() {
  lcd->selectUp();
}

void ScreenMain::selectDown() {
  lcd->selectDown();
}

void ScreenMain::selectLeft() {
  lcd->selectLeft();
}

void ScreenMain::selectRight() {
  lcd->selectRight();
}

MainMenuPosition ScreenMain::getSelectedPosition() {
  return lcd->getSelectedPosition();
}

void ScreenMain::startMainMenuSelection() {
  lcd->startSelection();
}

