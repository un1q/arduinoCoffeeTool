//Libraries:
//https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads/ <- no more, since we changed display
//https://playground.arduino.cc/code/keypad#Download
//https://github.com/milesburton/Arduino-Temperature-Control-Library/releases
//  Arduino-Temperature-Control-Library contains OneWire, but 
//  just in case you want to have a different verstion of OneWire
//  I provide the link: https://github.com/PaulStoffregen/OneWire/releases
//https://botland.com.pl/index.php?controller=attachment&id_attachment=1222
//  this is HX711.h library

#include "melody.h"
#include "pitches.h"
#include "main_loop.h"
#include "globals.h"
#include "debug.h"

#include <Keypad.h>

//Buzzer (use resistor ~100R)
#define PIN_BUZZ    13

//weight pins
#define SCALE_DOUT 11
#define SCALE_CLK  10
#define SCALE_CHK  9
const float scaleCalibrationFactor = 850;

//4x3 keypad PINs:
byte rowPins[4] = {A3, A4, A5, 2};
byte colPins[3] = {A0, A1, A2};

//temperature sensor is on PIN 12, use 4.7R)

//LCD_PINS: SCLK, DIN, DC, CS, RST (RST: -1 if not used)
#define LCD_PINS 3, 4, 5, 6, -1

Melody               alarmMelody     (new int[8] {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4}, new int[8] {4, 8, 8, 4, 4, 4, 4, 4}, 8);
Melody               timerStartMelody(new int[3] {NOTE_C3, NOTE_D3, NOTE_E3}, new int[3] {8, 8, 4}, 3);
Lcd                  *lcd           = new Lcd_N5110(LCD_PINS);
Keyboard             keyboard       = Keyboard(rowPins, colPins);
MeasureWeight        measureWeight  = MeasureWeight(SCALE_DOUT, SCALE_CLK, scaleCalibrationFactor, SCALE_CHK);
MeasureTemperature   measureTemp    = MeasureTemperature();
MeasureTime          measureTime    = MeasureTime();
ActionMelody         alarmAction    = ActionMelody(&alarmMelody);
MeasureTime          measureTimeout = MeasureTime();


void setup() {
  Melody::setPin(PIN_BUZZ);
  Serial.begin(9600);
  SerialMsg("BEGIN");
  SerialFreeMemLog();

  lcd->setup();
  measureWeight.setup();
  mainLoopStartup();
}

void loop() {
  mainLoop();
}
