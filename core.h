#ifndef CORE_H_
#define CORE_H_

// Abstract class
// Each core classes is responsible for one screen (like main screen, main menu screen, options screen, timer screen etc.)
// update(key) should be colled each loop

class Core {
  public:
    static const int FOLLOW_RECIPE_END = 31;
    static const int MAIN_MENU         = 32;
  public:
    virtual ~Core();
    virtual int  update(char key) = 0; //return core type device should be switched to; everything below FOLLOW_RECIPE_END is a number of recipe; -1 means no change
    virtual void start()          = 0;
};

#endif