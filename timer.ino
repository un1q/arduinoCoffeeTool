//#include <Wire.h>
//#include <LiquidCrystal_I2C.h>
//
#include "melody.h"

#define PIN_BUZZ A0
#define PIN_BTN  A5

// notes in the melody:
unsigned long timerState = 0;

Melody melody(PIN_BUZZ);

void setup() {
  pinMode(PIN_BUZZ, OUTPUT);
  pinMode(PIN_BTN, INPUT);
}

void loop() {
  if (btnState()) {
    startTimer(1);
  }
  if (checkTimer())
    melody.play();
  delay(50);
}

bool checkTimer() {
  unsigned long time = millis();
  if (timerState == 0)
    return false;
  if (timerState <= time) {
    timerState = 0;
    return true;
  }
  return false;
}

void startTimer(unsigned long seconds) {
  timerState = millis() + seconds * 1000;
}

bool btnState() {
  return digitalRead(PIN_BTN) == HIGH;
}
