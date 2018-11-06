//Libraries:
//https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads/
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
//#include "lcd_16x2.h"
#include "lcd_N5110.h"
#include "measure_weight.h"

#include <Keypad.h>

//  LCM 1602 PINs:
//    SCL -> A5
//    SDA -> A4 

//Buzzer (use resistor ~100R)
#define PIN_BUZZ    A0

//weight pins
#define SCALE_DOUT 12
#define SCALE_CLK  11
const float scaleCalibrationFactor = 850;

//4x3 keypad PINs:
byte rowPins[4] = {5, 4, 3, 2};
byte colPins[3] = {8, 7, 6};

//temperature sensor is on PIN 10, use 4.7R)

Melody        melody(PIN_BUZZ);
Melody        buzz(PIN_BUZZ, new int[2] {NOTE_C4, NOTE_C4}, new int[2] {4,4}, 2);
//Lcd_16x2     lcd          = Lcd_16x2();
Lcd_N5110     lcd          = Lcd_N5110(A1,A2,A3,A4,-1);
Keyboard      keyboard     = Keyboard(rowPins, colPins);
MeasureWeight scale       = MeasureWeight(SCALE_DOUT, SCALE_CLK, scaleCalibrationFactor);
MainLoop      *mainLoop;

void setup() {
  Serial.begin(9600);
  Serial.println("SETUP");
  pinMode(PIN_BUZZ, OUTPUT);
  lcd.setup();
  scale.setup();
  mainLoop = new MainLoop(&scale, &keyboard, &lcd, &melody, &buzz);
  mainLoop->startup();
}

void loop() {
  mainLoop->loop();
}
