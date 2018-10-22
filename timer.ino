#include "melody.h"
#include "lcd.h"
#include "pitches.h"
#include "keyboard.h"
#include "core_timer.h"
#include "core_temp.h"

#include <Keypad.h>

//  LCM 1602 PINs:
//    SCL -> A5
//    SDA -> A4 
#define PIN_BUZZ    A0
#define PIN_BTN     A1

byte rowPins[4] = {3, 2, 1, 0}; //4x3 keypad PINs
byte colPins[3] = {6, 5, 4};    //4x3 keypad PINs

Melody   melody(PIN_BUZZ);
Melody   buzz(PIN_BUZZ, new int[2] {NOTE_C4, NOTE_C4}, new int[2] {4,4}, 2);
Lcd      lcd;
Keyboard keyboard = Keyboard(rowPins, colPins);

CoreTimer coreTimer = CoreTimer(&melody, &buzz);
CoreTemp  coreTemp  = CoreTemp();

void setup() {
  pinMode(PIN_BUZZ, OUTPUT);
  pinMode(PIN_BTN, INPUT);
  lcd.setup(&coreTimer, &coreTemp);
}

void loop()
{
  keyboard.loop();
  if (keyboard.getKey() == '#')
    coreTimer.startDrip();
  coreTimer.loop();
  coreTemp.loop();
  lcd.loop();
}

bool btnState() {
  return digitalRead(PIN_BTN) == HIGH  || keyboard.getKey() == 'D';
}
