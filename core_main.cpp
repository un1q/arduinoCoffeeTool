#include "core_main.h"

CoreMain::CoreMain() {
}

CoreMain::~CoreMain() {
}

void CoreMain::start() {
  keyboard.setShiftMode(shift_always);
  lcd->clear();
}

void CoreMain::update(char key) {
  switch (key) {
    case k_CLEAR: //k_CLEAR is shifted k_ENTER
      followRecipe.start();
      break;
    case '0': 
    case '.': 
      followRecipe.stop();
      measureWeight.tare();
      break;
    case k_F1: useRecipe(0); break;
    case k_F2: useRecipe(1); break;
    case k_F3: useRecipe(2); break;
    case k_F4: useRecipe(3); break;
    case k_F5: useRecipe(4); break;
    case k_DOWN: followRecipe.foreward(); break;
    case k_UP  : followRecipe.backward(); break;
    case k_LEFT: followRecipe.stop(); gotoMenu(); return;
  }
  measureTemp.loop();
  followRecipe.check();
  printMainScreen();
}

void CoreMain::useRecipe(int i) {
  if (i < 0 || i >= Recipe::allCount)
    return;
  Recipe* p = Recipe::all[i];
  if (p != nullptr)
    followRecipe.prepare(p);
}

void CoreMain::printMainScreen() {
  SensorAlarm *alarm = followRecipe.getAlarm();
  lcdInfo.temp        = measureTemp.get();
  lcdInfo.time        = measureTime.get();
  lcdInfo.weight      = measureWeight.get();
  lcdInfo.alarmDesc   = followRecipe.alarmDesc.get();
  lcdInfo.step        = followRecipe.getText(&stepTextBuffer);
  lcdInfo.nextStep    = followRecipe.getTextNext(&nextStepTextBuffer);
  lcd->print(&lcdInfo);
}
