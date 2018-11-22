#include "core_main_menu.h"
#include "recipe.h"

CoreMainMenu::CoreMainMenu() {
  menu.size     = Recipe::allCount + 1;
  menu.selected = 0;
  menu.options  = new char*[menu.size];
  for (int i=0; i<Recipe::allCount; i++) {
    menu.options[i] = Recipe::all[i]->name;
  }
  menu.options[Recipe::allCount] = "timer";
}

CoreMainMenu::~CoreMainMenu() {
  delete(menu.options);
  menu.size = 0;
}

void CoreMainMenu::start() {
  keyboard.setShiftMode(shift_always);
  lcd->clear();
}

int CoreMainMenu::update(char key) {
  switch (key) {
    case k_F1: if (0 <= menu.size - 1) return 0; break;
    case k_F2: if (1 <= menu.size - 1) return 1; break;
    case k_F3: if (2 <= menu.size - 1) return 2; break;
    case k_F4: if (3 <= menu.size - 1) return 3; break;
    case k_F5: if (4 <= menu.size - 1) return 4; break;
    case k_UP   : menu.selected = menu.selected == 0 ? menu.size-1 : menu.selected-1 ; break;
    case k_DOWN : menu.selected = menu.selected == menu.size-1 ? 0 : menu.selected+1 ; break;
    case k_RIGHT:
    case k_CLEAR: 
      if (menu.selected >= Recipe::allCount)
        return Core::CORE_TIMER;
      else
        return menu.selected;
  }
  printMainScreen();
  return -1;
}

void CoreMainMenu::printMainScreen() {
  lcd->print(&menu);
}
