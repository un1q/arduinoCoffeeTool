#include "keyboard.h"

Keyboard::Keyboard(byte* rowPins, byte* colPins) :
    rowPins(rowPins),
    colPins(colPins) {
  keymap        = makeKeymap(keys);
  keymapShifted = makeKeymap(keysShifted);
  keypad        = new Keypad( keymap, rowPins, colPins, rows, cols );
}

Keyboard::~Keyboard() {
  delete(keypad);
}

char Keyboard::getKey() {
  return key;
}

void Keyboard::loop() {
  key = keypad->getKey();
  if (key == '*') {
    shifted = !shifted;
    keypad->begin(shifted ? keymapShifted : keymap);
  } else if(shifted) {
    shifted = false;
  }
}