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
  
  RecipeStep(OnStart onStart, FlashAddr text, SensorType sensorType, int value, int buzzMargin, int timeoutIfNoSensor, bool autoNext);
  ~RecipeStep();
  Sensor*     getSensor();
  Alarm::Mode getAlarmMode();
};

struct Recipe {
  const static Recipe  drip;
  const static int     allCount;
  const static Recipe* all[];
  
  char*       name;
  int         stepsCount;
  RecipeStep* steps;
  
  Recipe(char* name, int count, RecipeStep *steps);
  ~Recipe();
};
#endif
