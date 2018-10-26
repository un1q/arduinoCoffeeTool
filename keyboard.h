#ifndef KEYBOARD_H_
#define KEYBOARD_H_

// keypad class
//
// keypad has 4x3 dimension:
//   '1','2','3'
//   '4','5','6'
//   '7','8','9'
//   '*','0','#'
//
// '*' may work like shift
// if shift mode is on, '*' changes keypad into:
//   'd','U','e'
//   'L','c','R'
//   'a','D','b'
//   '*','.','C'
// 'U','L','R','D' means up, left, right, down
// 'C' means clear
// 'a','b','c','d','e' means F1, F2, F3, F4, F5

#include <Keypad.h>

enum ShiftMode {
  shift_off,     //shift button doesn't work as shift
  shift_normal,  //shift button changes next character
  shift_sticky   //shift button works like caps lock
};

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
  char*     keymap;
  char*     keymapShifted;
  byte*     rowPins;
  byte*     colPins;
  Keypad*   keypad;
  char      key;
  bool      shifted   = false;
  ShiftMode shiftMode = shift_off;
public:
  
  Keyboard(byte* rowPins, byte* colPins);
  ~Keyboard();
  char getKey();
  void loop();
  void setShiftMode(ShiftMode);
  void setShiftState(bool);
};

#endif
