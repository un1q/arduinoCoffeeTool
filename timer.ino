#include "melody.h"
#include "timer.h"
#include "lcd.h"
#include "pitches.h"
#include "keyboard.h"

#include <Keypad.h>

//  LCM 1602 PINs:
//    SCL -> A5
//    SDA -> A4 
#define PIN_BUZZ    A0
#define PIN_BTN     A1

byte rowPins[4] = {3, 2, 1, 0}; //4x4 keypad PINs
byte colPins[4] = {7, 6, 5, 4}; //4x4 keypad PINs

Melody melody(PIN_BUZZ);
Melody buzz(PIN_BUZZ, new int[2] {NOTE_C4, NOTE_C4}, new int[2] {4,4}, 2);
Timer  timer;
Lcd    lcd;
Keyboard keyboard = Keyboard(rowPins, colPins);

int* dripTiming = new int[4] {3, 33, 33+60, 33+60+60};
int  dripTimingCount = 4;

void setup() {
  pinMode(PIN_BUZZ, OUTPUT);
  pinMode(PIN_BTN, INPUT);
  lcd.init();
}

void loop() {
  static bool buzzed = false;
  if (btnState()) {
    timer.setSeconds(dripTiming, dripTimingCount);
    buzzed = false;
  }
  int sec = timer.getSeconds();
  if (sec == 0) {
    lcd.music();
    melody.play();
    timer.nextAlarm();
    buzzed = false;
  } else if (!buzzed && sec>5 && sec <= 10) {
    buzz.play();
    buzzed = true;
  }
  lcd.timer(&timer);
  delay(50);
}

bool btnState() {
  return digitalRead(PIN_BTN) == HIGH  || keyboard.getKey() == 'D';
}
