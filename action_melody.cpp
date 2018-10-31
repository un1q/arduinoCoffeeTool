#include "action_melody.h"

ActionMelody::ActionMelody(Melody *melody) {
  this->melody = melody;
}

ActionMelody::~ActionMelody() {
}

void ActionMelody::doIt() {
  melody->play();
}