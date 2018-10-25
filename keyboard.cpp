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
  if (key == '*' && shiftMode != shift_off) {
    setShiftState(!shifted);
  } else if(shifted && shiftMode == shift_normal) {
    setShiftState(false);
  }
}

void Keyboard::setShiftState(bool state) {
  if (state == shifted)
    return;
  shifted = state;
  keypad->begin(shifted ? keymapShifted : keymap);
}

void Keyboard::setShiftMode(ShiftMode shiftMode) {
  if (shiftMode == this->shiftMode)
    return;
  this->shiftMode = shiftMode;
  if (shiftMode == shift_off && shifted) {
    setShiftState(false);
  }
}