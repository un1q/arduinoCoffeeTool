#include "core_follow_recipe.h"

CoreFollowRecipe::CoreFollowRecipe() {
}

CoreFollowRecipe::CoreFollowRecipe(int recipeId) {
  useRecipe(recipeId);
}

CoreFollowRecipe::~CoreFollowRecipe() {
}

void CoreFollowRecipe::start() {
  keyboard.setShiftMode(shift_always);
  lcd->clear();
}

int CoreFollowRecipe::update(char key) {
  switch (key) {
    case k_CLEAR: //k_CLEAR is shifted k_ENTER
      followRecipe.foreward();
      break;
    case '0': 
    case '.': 
      followRecipe.start();
      //measureWeight.tare();
      break;
    case k_F1: useRecipe(0); break;
    case k_F2: useRecipe(1); break;
    case k_F3: useRecipe(2); break;
    case k_F4: useRecipe(3); break;
    case k_F5: useRecipe(4); break;
    case k_DOWN: followRecipe.foreward(); break;
    case k_RIGHT:
    case k_UP  : followRecipe.backward(); break;
    case k_LEFT: followRecipe.stop(); return Core::MAIN_MENU; return;
  }
  measureTemp.loop();
  followRecipe.check();
  printMainScreen();
  return -1;
}

void CoreFollowRecipe::useRecipe(int i) {
  if (i < 0 || i >= Recipe::allCount)
    return;
  Recipe* p = Recipe::all[i];
  if (p != nullptr) {
    followRecipe.prepare(p);
    followRecipe.start();
  }
}

void CoreFollowRecipe::printMainScreen() {
  SensorAlarm *alarm = followRecipe.getAlarm();
  lcdInfo.temp        = measureTemp.get();
  lcdInfo.time        = measureTime.get();
  lcdInfo.weight      = measureWeight.get();
  lcdInfo.alarmDesc   = followRecipe.getAlarmDesc();
  lcdInfo.step        = followRecipe.getText();
  lcdInfo.nextStep    = followRecipe.getTextNext();
  lcd->print(&lcdInfo);
}
