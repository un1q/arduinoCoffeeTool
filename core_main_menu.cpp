#include "core_main_menu.h"
#include "recipe.h"

CoreMainMenu::CoreMainMenu() {
  menu.size     = Recipe::allCount;
  menu.selected = 0;
  menu.options  = new char*[menu.size];
  for (int i=0; i<menu.size; i++) {
    menu.options[i] = Recipe::all[i]->name;
  }
}

CoreMainMenu::~CoreMainMenu() {
  delete(menu.options);
  menu.size = 0;
}

void CoreMainMenu::start() {
  keyboard.setShiftMode(shift_always);
  lcd->clear();
}

void CoreMainMenu::update(char key) {
  switch (key) {
    case k_UP   : menu.selected = menu.selected == 0 ? menu.size-1 : menu.selected-1 ; break;
    case k_DOWN : menu.selected = menu.selected == menu.size-1 ? 0 : menu.selected+1 ; break;
    case k_LEFT : ; break;
    case k_RIGHT:
    case k_CLEAR: selected(menu.selected); return; //k_CLEAR is shifted k_ENTER
  }
  printMainScreen();
}

void CoreMainMenu::printMainScreen() {
  lcd->print(&menu);
}
