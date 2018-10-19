#include "melody.h"
#include "lcd.h"
#include "pitches.h"
#include "keyboard.h"
#include "core.h"
#include "core_timer.h"
#include "core_temp.h"

#include <Keypad.h>

//  LCM 1602 PINs:
//    SCL -> A5
//    SDA -> A4 
#define PIN_BUZZ    A0
#define PIN_BTN     A1

byte rowPins[4] = {3, 2, 1, 0}; //4x4 keypad PINs
byte colPins[4] = {7, 6, 5, 4}; //4x4 keypad PINs

Melody   melody(PIN_BUZZ);
Melody   buzz(PIN_BUZZ, new int[2] {NOTE_C4, NOTE_C4}, new int[2] {4,4}, 2);
Lcd      lcd;
Keyboard keyboard = Keyboard(rowPins, colPins);

CoreTimer coreTimer = CoreTimer(&melody, &buzz);
CoreTemp  coreTemp  = CoreTemp();
Core      *core;

void setup() {
  pinMode(PIN_BUZZ, OUTPUT);
  pinMode(PIN_BTN, INPUT);
  lcd.init();
  coreTimer.setup(&lcd);
  coreTemp.setup(&lcd);
  setCore(&coreTemp);
}

void loop()
{
  char key = keyboard.getKey();
  if (key == 'A') 
    setCore(&coreTimer);
  else if (key == 'B')
    setCore(&coreTemp);
  core->loop(key);
}

void setCore(Core *newCore) {
  newCore->start();
  core = newCore;
}

bool btnState() {
  return digitalRead(PIN_BTN) == HIGH  || keyboard.getKey() == 'D';
}
