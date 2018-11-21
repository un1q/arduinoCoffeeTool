#include "main_loop.h"
#include "debug.h"

CoreMain     coreMain     = CoreMain    ();
CoreMainMenu coreMainMenu = CoreMainMenu();
Core         *core        = nullptr;

void mainLoopStartup() {
  coreMain.gotoMenu     = [](){ changeCore(&coreMainMenu); };
  coreMainMenu.selected = [](int i){
    changeCore(&coreMain);
    coreMain.useRecipe(i);
  };
  changeCore(&coreMainMenu);
}

void mainLoop() {
  keyboard.loop();
  char key = keyboard.getKey();
  core->update(key);
  if (key == k_SHIFT)
    SerialFreeMemLog();
}


void changeCore(Core *newCore) {
  if (core == newCore)
    return;
  core = newCore;
  core->start();
}
