//#include <Wire.h>
//#include <LiquidCrystal_I2C.h>
//
#include "melody.h"
#include "timer.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define PIN_BUZZ    A0
#define PIN_BTN     A1
#define LCD_ADDRESS 0x3F


Melody melody(PIN_BUZZ);
Timer  timer;
LiquidCrystal_I2C lcd(LCD_ADDRESS, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
  pinMode(PIN_BUZZ, OUTPUT);
  pinMode(PIN_BTN, INPUT);
  lcd.begin(16,2);
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Timer");
}

void loop() {
  if (btnState()) {
    timer.setSeconds(10);
  }
  if (timer.getSeconds() == 0) {
    timer.off();
    lcd.setCursor(0,1);
    lcd.print("!!!!");
    melody.play();
  }
  lcd.setCursor(0,1);
  lcd.print(timer.getSecondsStr());
  delay(100);
}

bool btnState() {
  return digitalRead(PIN_BTN) == HIGH;
}
