#ifndef RECIPE_H_
#define RECIPE_H_

#include "string_buffer.h"
#include "sensor.h"
#include "alarm.h"

enum SensorType {MEASURE_WEIGHT=0, MEASURE_TEMP, MEASURE_TIME, PRESS_BUTTON};
enum OnStart    {ONSTART_NOTHING=0, ONSTART_TARE, ONSTART_START_TIMER};


struct RecipeStep {
  OnStart    onStart          ;
  FlashAddr  text             ;
  SensorType sensorType       ;
  int        value            ;
  int        buzzMargin       ;
  int        timeoutIfNoSensor;
  bool       autoNext         ;
  
  //RecipeStep();
  //RecipeStep(OnStart onStart, FlashAddr text, SensorType sensorType, int value, int buzzMargin, int timeoutIfNoSensor, bool autoNext);
  //~RecipeStep();
  Sensor*     getSensor();
  Alarm::Mode getAlarmMode();
};

typedef RecipeStep* FlashRecipeSteps;

class Recipe {
  public:
    const static Recipe  drip;
    const static Recipe  chemex;
    const static Recipe  fellow;
    const static Recipe  tea;
    const static int     allCount;
    const static Recipe* all[];
  private:
    FlashRecipeSteps steps;
  public:
    int         stepsCount;
    char*       name;
  public:
    Recipe(char* name, int count, FlashRecipeSteps steps);
    ~Recipe();
    bool getStep(int i, RecipeStep *dest);
};
#endif
