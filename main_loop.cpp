#include "main_loop.h"
#include "debug.h"
#include "recipe.h"
#include "core_follow_recipe.h"
#include "core_main_menu.h"
#include "core_timer.h"

Core  *core      = nullptr;
int   actualCore = -1;

CoreFollowRecipe *corePreheat = nullptr; //preheat

unsigned long lastLogTime = 0;
static const unsigned long logFreq = 1000ul;


void mainLoopStartup() {
  //corePreheat = new CoreFollowRecipe(0);
  changeCore(Core::MAIN_MENU);
  SerialFreeMemLog();
}

void mainLoop() {
  keyboard.loop();
  char key = keyboard.getKey();
  SerialLogIf(key > 0, key);
  int newCoreId = core->update(key);
  changeCore( newCoreId );
  if (key == k_SHIFT)
    SerialFreeMemLog();
  logSensors();
}

void changeCore(int coreId) {
  if (coreId == -1 || actualCore == coreId)
    return;
  actualCore = coreId;
  SerialLog(coreId);
  if (core)
    delete(core);
  switch (coreId) {
    case Core::MAIN_MENU:
      core = new CoreMainMenu();
      break;
    case Core::CORE_TIMER:
      core = new CoreTimer();
      break;
    default:
      if (coreId >= 0 && coreId < Recipe::allCount) {
        if (corePreheat) {
          core = corePreheat;
          if (coreId != 0)
            corePreheat->useRecipe(coreId);
          corePreheat = nullptr;
        } else {
          core = new CoreFollowRecipe(coreId);
        }
      } else {
        core = new CoreMainMenu();
      }
      break;
  }
  core->start();
}

void logSensors() {
  unsigned long now = millis();
  if (now < lastLogTime || now - lastLogTime >= logFreq) {
    lastLogTime = now;
    Serial.print(F("[sensors];"));
    Serial.print(now);
    Serial.print(';');
    Serial.print(measureTemp.get());
    Serial.print(';');
    Serial.print(measureTime.get());
    Serial.print(';');
    Serial.println(measureWeight.get());
    Serial.flush();
  }
}
