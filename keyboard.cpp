#include "keyboard.h"

Keyboard::Keyboard(byte* rowPins, byte* colPins) :
    rowPins(rowPins),
    colPins(colPins) {
  keypad = new Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );
}

Keyboard::~Keyboard() {
  delete(keypad);
}

char Keyboard::getKey() {
  return keypad->getKey();
}