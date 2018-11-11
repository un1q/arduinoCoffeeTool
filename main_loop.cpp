#include "main_loop.h"

CoreMain     *MainLoop::coreMain     = nullptr;
CoreMainMenu *MainLoop::coreMainMenu = nullptr;
Core         *MainLoop::core         = nullptr;

MainLoop::MainLoop(Melody* alarmMelody, Melody* buzzMelody) {
  this->alarmAction    = new ActionMelody(alarmMelody);
  this->buzzAction     = new ActionMelody(buzzMelody);
  this->alarmTimer     = new AlarmTimer(nullptr, alarmAction, buzzAction); //nullptr = no preset
  this->coreMain       = new CoreMain    (alarmTimer);
  this->coreMainMenu   = new CoreMainMenu();
  coreMain->gotoMenu     = [](){ changeCore(coreMainMenu); };
  coreMainMenu->selected = [](int i){
    changeCore(coreMain);
    coreMain->usePreset(i);
  };
}

MainLoop::~MainLoop() {
  delete(alarmAction );
  delete(buzzAction  );
  delete(alarmTimer  );
  delete(coreMain    );
  delete(coreMainMenu);
}

void MainLoop::startup() {
  //MainLoop::changeCore(coreMain);
  MainLoop::changeCore(coreMainMenu);
}

void MainLoop::loop() {
  keyboard.loop();
  char key = keyboard.getKey();
  core->update(key);
}


void MainLoop::changeCore(Core *core) {
  if (MainLoop::core == core)
    return;
  MainLoop::core = core;
  core->start();
}
