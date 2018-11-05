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
  if (key == k_SHIFT) {
    if (shiftMode == shift_normal || shiftMode == shift_sticky)
      shiftPressed = !shiftPressed;
  } else {
    if (shiftMode != shift_sticky)
      shiftPressed = false;
  }
  updateShiftState();
}

void Keyboard::setShiftState(bool state) {
  if (state == shifted)
    return;
  shifted = state;
  keypad->begin(shifted ? keymapShifted : keymap);
}

void Keyboard::updateShiftState() {
  switch (shiftMode) {
    case shift_off   :
      setShiftState(false);
      break;
    case shift_normal:
    case shift_sticky:
      setShiftState(shiftPressed);
      break;
    case shift_always: 
      setShiftState(true);
      break;
  }
}

void Keyboard::setShiftMode(ShiftMode shiftMode) {
  if (shiftMode == this->shiftMode)
    return;
  this->shiftMode = shiftMode;
  shiftPressed = false;
  updateShiftState();
}