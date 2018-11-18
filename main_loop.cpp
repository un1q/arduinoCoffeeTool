#include "main_loop.h"

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
}


void changeCore(Core *newCore) {
  if (core == newCore)
    return;
  core = newCore;
  core->start();
}
