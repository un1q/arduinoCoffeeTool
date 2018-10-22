#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <Keypad.h>

class Keyboard {
  const byte rows = 4; //four rows
  const byte cols = 3; //three columns
  char keys[4][3] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
  };
  char keysShifted[4][3] = {
    {'d','U','e'},
    {'L','c','R'},
    {'a','D','b'},
    {'*','.','C'}
  };
  char*   keymap;
  char*   keymapShifted;
  byte*   rowPins;
  byte*   colPins;
  Keypad* keypad;
  char    key;
public:
  bool shifted = false;
  
  Keyboard(byte* rowPins, byte* colPins);
  ~Keyboard();
  char getKey();
  void loop();
};

#endif
