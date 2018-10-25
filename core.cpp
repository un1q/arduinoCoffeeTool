#include "core.h"

Core::Core(CoreTimer* timer, CoreTemp* temp, Keyboard* keyboard, Lcd* lcd) {
  this->timer    = timer;
  this->temp     = temp ;
  this->keyboard = keyboard;
  this->lcd      = lcd;
}

void Core::loop() {
  keyboard->loop();
  char k = keyboard->getKey();
  switch (k) {
    case '#': timer->startDrip();
      break;
    case 'C': timer->stop();
      break;
  }
  timer->loop();
  temp ->loop();
  lcd  ->loop();
}
