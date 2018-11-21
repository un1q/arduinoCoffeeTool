#ifndef CORE_MAIN_H_
#define CORE_MAIN_H_

// Main screen
// Presents all sensors output and all alarms on LCD
// Calls void (*gotoMenu)() when main menu should be presented
// User can also start timer in this mode

#include "globals.h"
#include "core.h"
#include "recipe.h"
#include "follow_recipe.h"

class CoreMain : public Core {
    FollowRecipe  followRecipe;
    Lcd::Info     lcdInfo;
    
    void printMainScreen();
  public:
    CoreMain();
    CoreMain(int recipeId);
    ~CoreMain();
    int  update(char key);
    void start();
    void useRecipe(int i);
};

#endif