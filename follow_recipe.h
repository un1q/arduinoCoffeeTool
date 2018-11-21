#ifndef FOLLOW_RECIPE_H_
#define FOLLOW_RECIPE_H_

#include "recipe.h"
#include "sensor_alarm.h"
#include "string_buffer.h"

class FollowRecipe {
  private:
    RecipeStep   actualStep;
    int          stepNr           = -1;
    Recipe       *recipe          = nullptr;
    SensorAlarm  *alarm           = nullptr;
    bool         isTimeout        = false;
    StringBuffer *textBuffer      = nullptr;
    StringBuffer *nextTextBuffer  = nullptr;
    StringBuffer *alarmDescBuffer = nullptr;
  public:
    FollowRecipe();
    ~FollowRecipe();
    void         prepare(const Recipe *recipe);
    void         start();
    void         stop();
    void         foreward();
    void         backward();
    bool         check(); //returns true if step is finished
    char*        getText     ();
    char*        getTextNext ();
    char*        getAlarmDesc();
    RecipeStep*  getStep();
    SensorAlarm* getAlarm();
  private:
    void         clean();
    void         update();
};
#endif
