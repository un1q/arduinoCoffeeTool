#ifndef RECIPE_H_
#define RECIPE_H_

#include "sensor_alarm.h"
#include "string_buffer.h"

enum SensorType {MEASURE_WEIGHT=0, MEASURE_TEMP, MEASURE_TIME, PRESS_BUTTON};
enum OnStart    {ONSTART_NOTHING=0, ONSTART_TARE, ONSTART_START_TIMER};

struct RecipeStep {
  OnStart    onStart          ;
  FlashAddr  text             ;
  bool       buzz             ;
  SensorType sensorType       ;
  int        value            ;
  int        buzzValue        ;
  int        timeoutIfNoSensor;
  bool       autoNext         ;
  
  RecipeStep(OnStart onStart, FlashAddr text, SensorType sensorType, int value, int buzzValue, bool buzz, int timeoutIfNoSensor, bool autoNext);
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

class FollowRecipe {
  public:
    StringBuffer alarmDesc;
  private:
    int          step       = -1;
    Recipe       *recipe    = nullptr;
    SensorAlarm  *alarm     = nullptr;
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
};
#endif
