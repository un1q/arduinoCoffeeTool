//Libraries:
//https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads/
//https://playground.arduino.cc/code/keypad#Download
//https://github.com/milesburton/Arduino-Temperature-Control-Library/releases
//  previous library contains this, so you do not need this, but 
//  just in case: https://github.com/PaulStoffregen/OneWire/releases

#include "melody.h"
#include "pitches.h"
#include "core.h"

#include <Keypad.h>

//  LCM 1602 PINs:
//    SCL -> A5
//    SDA -> A4 

//Buzzer (use resistor ~100R)
#define PIN_BUZZ    A0

//4x3 keypad PINs:
byte rowPins[4] = {3, 2, 1, 0};
byte colPins[3] = {6, 5, 4};

//temperature sensor is on PIN 10, use 4.7R)

Melody     melody(PIN_BUZZ);
Melody     buzz(PIN_BUZZ, new int[2] {NOTE_C4, NOTE_C4}, new int[2] {4,4}, 2);
Lcd        lcd;
Keyboard   keyboard = Keyboard(rowPins, colPins);
CoreTimer  coreTimer = CoreTimer(&melody, &buzz);
CoreTemp   coreTemp  = CoreTemp();
Core       core      = Core(&coreTimer, &coreTemp, &keyboard, &lcd);

void setup() {
  pinMode(PIN_BUZZ, OUTPUT);
  lcd.setup();
}

void loop() {
  core.loop();
}
