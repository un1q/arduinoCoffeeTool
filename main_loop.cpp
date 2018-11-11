#include "main_loop.h"

CoreMain     *MainLoop::coreMain     = nullptr;
CoreMainMenu *MainLoop::coreMainMenu = nullptr;
Core         *MainLoop::core         = nullptr;

MainLoop::MainLoop(MeasureWeight* measureWeight, Melody* alarmMelody, Melody* buzzMelody) {
  this->alarmAction    = new ActionMelody(alarmMelody);
  this->buzzAction     = new ActionMelody(buzzMelody);
  this->measureTime    = new MeasureTime();
  this->alarmTimer     = new AlarmTimer(measureTime, nullptr, alarmAction, buzzAction);
  this->temp           = new Temperature();
  this->measureWeight  = measureWeight;
  this->coreMain       = new CoreMain    (alarmTimer, temp, measureWeight);
  this->coreMainMenu   = new CoreMainMenu(alarmTimer, temp);
  coreMain->gotoMenu     = [](){ changeCore(coreMainMenu); };
  coreMainMenu->selected = [](int i){
    changeCore(coreMain);
    coreMain->usePreset(i);
  };
}

MainLoop::~MainLoop() {
  delete(alarmAction );
  delete(buzzAction  );
  delete(measureTime );
  delete(alarmTimer  );
  delete(temp        );
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
