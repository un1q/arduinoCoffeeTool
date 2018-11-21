#include "main_loop.h"
#include "debug.h"
#include "recipe.h"
#include "core_follow_recipe.h"
#include "core_main_menu.h"
#include "core_timer.h"

Core  *core      = nullptr;
int   actualCore = -1;

CoreFollowRecipe *corePreheat = nullptr; //preheat

void mainLoopStartup() {
  changeCore(Core::MAIN_MENU);
  corePreheat = new CoreFollowRecipe(0);
  SerialFreeMemLog();
}

void mainLoop() {
  keyboard.loop();
  char key = keyboard.getKey();
  int newCoreId = core->update(key);
  changeCore( newCoreId );
  if (key == k_SHIFT)
    SerialFreeMemLog();
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
