#include "main_loop.h"

CoreMain     *MainLoop::coreMain;
CoreMainMenu *MainLoop::coreMainMenu;
Core         *MainLoop::core;

MainLoop::MainLoop(Keyboard* keyboard, Lcd* lcd, Melody* alarmMelody, Melody* buzzMelody) {
  this->alarmAction    = new ActionMelody(alarmMelody);
  this->buzzAction     = new ActionMelody(buzzMelody);
  this->measureTime    = new MeasureTime();
  this->alarmTimer     = new AlarmTimer(measureTime, &TimerPreset::drip, alarmAction, buzzAction);
  this->temp           = new Temperature();
  this->keyboard       = keyboard;
  this->lcd            = lcd;
  this->coreMain       = new CoreMain    (alarmTimer, temp, keyboard, lcd);
  this->coreMainMenu   = new CoreMainMenu(alarmTimer, temp, keyboard, lcd);
  coreMain->gotoMenu   = [](){ changeCore(coreMainMenu); };
  coreMainMenu->goBack = [](){ changeCore(coreMain); };
}

MainLoop::~MainLoop() {
  delete(alarmAction );
  delete(buzzAction  );
  delete(measureTime );
  delete(alarmTimer  );
  delete(temp        );
  delete(keyboard    );
  delete(lcd         );
  delete(coreMain    );
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
