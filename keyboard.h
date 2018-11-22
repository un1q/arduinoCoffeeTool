#ifndef KEYBOARD_H_
#define KEYBOARD_H_

// keypad class
//
// keypad has 4x3 dimension:
//   '1','2','3'
//   '4','5','6'
//   '7','8','9'
//   '*','0','#'
// '#' is also known as k_ENTER
//
// '*' may work like shift
// if shift mode is on, '*' changes keypad into:
//  {k_F4   ,k_UP  ,k_F5   },
//  {k_LEFT ,k_F3  ,k_RIGHT},
//  {k_F1   ,k_DOWN,k_F2   },
//  {k_SHIFT,'.'   ,k_CLEAR}

#include <Keypad.h>

#define k_SHIFT  '*'
#define k_ENTER  '#'
#define k_CLEAR  'C'
#define k_F1     'a'
#define k_F2     'b'
#define k_F3     'c'
#define k_F4     'd'
#define k_F5     'e'
#define k_UP     '^'
#define k_DOWN   '_'
#define k_LEFT   '<'
#define k_RIGHT  '>'

enum ShiftMode {
  shift_off,     //shift button doesn't work as shift
  shift_normal,  //shift button changes next character
  shift_sticky,  //shift button works like caps lock
  shift_always   //shift is always on
};

class Keyboard {
  const byte rows = 4; //four rows
  const byte cols = 3; //three columns
  char keys[4][3] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {k_SHIFT,'0',k_ENTER}
  };
  char keysShifted[4][3] = {
    {k_F4   ,k_UP  ,k_F5   },
    {k_LEFT ,k_F3  ,k_RIGHT},
    {k_F1   ,k_DOWN,k_F2   },
    {k_SHIFT,'.'   ,k_CLEAR}
  };
  char*     keymap;
  char*     keymapShifted;
  byte*     rowPins;
  byte*     colPins;
  Keypad*   keypad;
  char      key;
  bool      shifted   = false;
  ShiftMode shiftMode = shift_off;
  bool      shiftPressed = false;
  
  void updateShiftState();
  void setShiftState(bool);
public:
  
  Keyboard(byte* rowPins, byte* colPins);
  ~Keyboard();
  char getKey();
  void loop();
  void setShiftMode(ShiftMode);
};

#endif
