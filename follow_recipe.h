#ifndef FOLLOW_RECIPE_H_
#define FOLLOW_RECIPE_H_

#include "recipe.h"
#include "sensor_alarm.h"
#include "string_buffer.h"

class FollowRecipe {
  private:
    int           stepNr           = -1;
    Recipe        *recipe          = nullptr;
    SensorAlarm   *alarm           = nullptr;
    bool          autoNext         = false;
    StringBuffer  *textBuffer      = nullptr;
    StringBuffer  *nextTextBuffer  = nullptr;
    StringBuffer  *alarmDescBuffer = nullptr;
    bool          sensorActive     = false;
  public:
    FollowRecipe();
    ~FollowRecipe();
    void         prepare(const Recipe *recipe);
    void         start();
    void         stop();
    void         foreward();
    void         backward();
    bool         check(); //returns true if step is finished
    RecipeStep*  getStep();
    char*        getAlarmDesc();
    inline char* getText     ();
    inline char* getTextNext ();
  private:
    void         clean();
    void         update();
};

//inline methods:

char* FollowRecipe::getText() {
  if (!textBuffer)
    return nullptr;
  return textBuffer->get();
}

char* FollowRecipe::getTextNext() {
  if (!nextTextBuffer)
    return nullptr;
  return nextTextBuffer->get();
}

#endif
