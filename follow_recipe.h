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
    RecipeStep*  getStep();
    inline char*        getText     ();
    inline char*        getTextNext ();
    inline char*        getAlarmDesc();
    inline SensorAlarm* getAlarm();
  private:
    void         clean();
    void         update();
};

//inline methods:

inline SensorAlarm* FollowRecipe::getAlarm() {
  return alarm;
}

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

char* FollowRecipe::getAlarmDesc() {
  if (!alarmDescBuffer)
    return nullptr;
  return alarmDescBuffer->get();
}

#endif
