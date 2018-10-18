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

int* dripTiming = new int[4] {3, 33, 33+60, 33+60+60};
int  dripTimingCount = 4;

void setup() {
  pinMode(PIN_BUZZ, OUTPUT);
  pinMode(PIN_BTN, INPUT);
  lcd.init();
}

void loop() {
  if (btnState()) {
    timer.setSeconds(dripTiming, dripTimingCount);
  }
  if (timer.getSeconds() == 0) {
    lcd.music();
    melody.play();
    timer.nextAlarm();
  }
  lcd.timer(&timer);
  delay(100);
}

bool btnState() {
  return digitalRead(PIN_BTN) == HIGH;
}
