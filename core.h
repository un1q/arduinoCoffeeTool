#ifndef CORE_H_
#define CORE_H_

// Abstract class
// Each core classes is responsible for one screen (like main screen, main menu screen, options screen, etc.)
// including:
// - checking all sensors used on this screen
// - updating all informations on LCD
// - reaction to keypad (keypad is handled in main loop and key is passed as argument)
// - reaction to other inputs if necessary
// if Core implementation wants to stop, it can provide some function pointer, for example
//   void (*gotoMenu)() = {};
// this function can be handled in main loop

class Core {
  public:
    virtual void update(char key) = 0;
    virtual void start()          = 0;
};

#endif