#include "action_start_timer.h"
#include "globals.h"

ActionStartTimer::ActionStartTimer() {
}

ActionStartTimer::~ActionStartTimer() {
}

void ActionStartTimer::doIt() {
  measureTime.start();
  timerStartMelody.play();

}