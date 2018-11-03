#include "main_loop.h"

CoreMain     *MainLoop::coreMain;
CoreMainMenu *MainLoop::coreMainMenu;
Core         *MainLoop::core;

    
MainLoop::MainLoop(AlarmTimer* timer, Temperature* temp, Keyboard* keyboard, Lcd* lcd) {
  this->timer          = timer;
  this->temp           = temp ;
  this->keyboard       = keyboard;
  this->lcd            = lcd;
  this->coreMain       = new CoreMain    (timer, temp, keyboard, lcd);
  this->coreMainMenu   = new CoreMainMenu(timer, temp, keyboard, lcd);
  coreMain->gotoMenu   = [](){ changeCore(coreMainMenu); };
  coreMainMenu->goBack = [](){ changeCore(coreMain); };
}

MainLoop::~MainLoop() {
  delete(coreMain);
  delete(coreMainMenu);
}

void MainLoop::startup() {
  MainLoop::changeCore(coreMain);
}

void MainLoop::loop() {
  keyboard->loop();
  char key = keyboard->getKey();
  core->update(key);
}


void MainLoop::changeCore(Core *core) {
  if (MainLoop::core == core)
    return;
  MainLoop::core = core;
  core->start();
  delay(50);
}
