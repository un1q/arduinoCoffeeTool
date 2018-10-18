#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <Keypad.h>

class Keyboard {
  const byte rows = 4; //four rows
  const byte cols = 4; //three columns
  char keys[4][4] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
  };
  byte*   rowPins;
  byte*   colPins;
  Keypad* keypad;
public:
  Keyboard(byte* rowPins, byte* colPins);
  ~Keyboard();
  char getKey();
};

#endif
