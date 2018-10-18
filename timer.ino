#include "melody.h"
#include "timer.h"
#include "lcd.h"

//  LCM 1602 PINs:
//    SCL -> A5
//    SDA -> A4 
#define PIN_BUZZ    A0
#define PIN_BTN     A1


Melody melody(PIN_BUZZ);
Timer  timer;
Lcd    lcd;

void setup() {
  pinMode(PIN_BUZZ, OUTPUT);
  pinMode(PIN_BTN, INPUT);
  lcd.init();
}

void loop() {
  if (btnState()) {
    timer.setSeconds(5);
  }
  if (timer.getSeconds() == 0) {
    timer.off();
    lcd.music();
    melody.play();
  }
  lcd.timer(&timer);
  delay(100);
}

bool btnState() {
  return digitalRead(PIN_BTN) == HIGH;
}
