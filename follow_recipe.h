#ifndef FOLLOW_RECIPE_H_
#define FOLLOW_RECIPE_H_

#include "recipe.h"
#include "sensor_alarm.h"
#include "string_buffer.h"

class FollowRecipe {
  public:
    StringBuffer alarmDesc;
  private:
    int          stepNr     = -1;
    Recipe       *recipe    = nullptr;
    SensorAlarm  *alarm     = nullptr;
    bool         isTimeout  = false;
    RecipeStep   actualStep;
  public:
    FollowRecipe();
    ~FollowRecipe();
    void         prepare(const Recipe *recipe);
    void         start();
    void         stop();
    void         foreward();
    void         backward();
    bool         check(); //returns true if step is finished
    char*        getText     (StringBuffer *buffer);
    char*        getTextNext (StringBuffer *buffer);
    char*        getAlarmDesc(StringBuffer *buffer);
    RecipeStep*  getStep();
    SensorAlarm* getAlarm();
  private:
    void         deleteAlarm();
    void         update();
};
#endif
