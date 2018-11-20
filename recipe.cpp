#include "recipe.h"
#include "globals.h"

Sensor* checkButton = nullptr;

//all recipes definition
const char str_odmierz_kawe[]   PROGMEM = "odmierz kawe"  ;
const char str_podgrzej_wode[]  PROGMEM = "podgrzej wode" ;
const char str_przygotuj_drip[] PROGMEM = "przygotuj drip";
const char str_zacznij_lac[]    PROGMEM = "zacznij lac"   ;
const char str_preinfuzja[]     PROGMEM = "preinfuzja"    ;
const char str_czekaj[]         PROGMEM = "czekaj"        ;
const char str_dolej[]          PROGMEM = "dolej"         ;
const char str_gotowe[]         PROGMEM = "gotowe"        ;

const Recipe Recipe::drip = Recipe("drip", 10, 
  new RecipeStep[10] { //it's like 160 bytes, so maybe we should keep it in flash memory?
    RecipeStep(ONSTART_TARE       , str_odmierz_kawe  , MEASURE_WEIGHT , 18 , -1 , 2 , false),
    RecipeStep(ONSTART_NOTHING    , str_podgrzej_wode , MEASURE_TEMP   , 85 , 10 , 2 , false),
    RecipeStep(ONSTART_NOTHING    , str_przygotuj_drip, PRESS_BUTTON   , -1 , -1 , -1, false),
    RecipeStep(ONSTART_TARE       , str_zacznij_lac   , MEASURE_WEIGHT , 2  , -1 , 2 , true ),
    RecipeStep(ONSTART_START_TIMER, str_preinfuzja    , MEASURE_WEIGHT , 40 , -1 , 2 , true ),
    RecipeStep(ONSTART_NOTHING    , str_czekaj        , MEASURE_TIME   , 30 , 10 , -1, true ),
    RecipeStep(ONSTART_NOTHING    , str_dolej         , MEASURE_WEIGHT , 150, -1 , 10, true ),
    RecipeStep(ONSTART_NOTHING    , str_czekaj        , MEASURE_TIME   , 90 , 10 , -1, true ),
    RecipeStep(ONSTART_NOTHING    , str_dolej         , MEASURE_WEIGHT , 250, -1 , 10, true ),
    RecipeStep(ONSTART_NOTHING    , str_gotowe        , MEASURE_TIME   , 210, 10 , -1, false)
  }
);

const int     Recipe::allCount = 1;
const Recipe* Recipe::all[Recipe::allCount] = { &drip };

//Recipe
Recipe::Recipe(char* name, int stepsCount, RecipeStep *steps) {
  this->name       = name;
  this->stepsCount = stepsCount;
  this->steps      = steps;
}

Recipe::~Recipe() {}

//RecipeStep

RecipeStep::RecipeStep(OnStart onStart, FlashAddr text, SensorType sensorType, int value, int buzzMargin, int timeoutIfNoSensor, bool autoNext) {
  this->onStart           = onStart          ;
  this->text              = text             ;
  this->sensorType        = sensorType       ;
  this->value             = value            ;
  this->buzzMargin        = buzzMargin        ;
  this->timeoutIfNoSensor = timeoutIfNoSensor;
  this->autoNext          = autoNext         ;
}

RecipeStep::~RecipeStep() {}

Sensor* RecipeStep::getSensor() {
  switch (sensorType) {
    case MEASURE_TEMP  : return &measureTemp;
    case MEASURE_TIME  : return &measureTime;
    case MEASURE_WEIGHT: return &measureWeight;
  }
  return nullptr;
}

Alarm::Mode RecipeStep::getAlarmMode() {
  switch (sensorType) {
    case MEASURE_TEMP  : return Alarm::crossing;
    case MEASURE_TIME  : return Alarm::crossingUp;
    case MEASURE_WEIGHT: return Alarm::crossing;
  }
  return Alarm::crossing;
}

