#include "recipe.h"
#include "globals.h"
#include "debug.h"

Sensor* checkButton = nullptr;

//all recipes definition
const char str_odmierz_kawe  [] PROGMEM = "odmierz kawe"  ;
const char str_podgrzej_wode [] PROGMEM = "podgrzej wode" ;
const char str_przygotuj_drip[] PROGMEM = "przygotuj drip";
const char str_zacznij_lac   [] PROGMEM = "zacznij lac"   ;
const char str_preinfuzja    [] PROGMEM = "preinfuzja"    ;
const char str_czekaj        [] PROGMEM = "czekaj"        ;
const char str_dolej         [] PROGMEM = "dolej"         ;
const char str_gotowe        [] PROGMEM = "gotowe"        ;
const char str_wsyp_kawe     [] PROGMEM = "wsyp kawe"     ;
const char str_wlej_50g_wody [] PROGMEM = "wlej 50g wody" ;
const char str_mieszaj       [] PROGMEM = "mieszaj"       ;
const char str_wycisnij      [] PROGMEM = "wycisnij"      ;
const char str_przygotuj_chem[] PROGMEM = "przygotuj sie ";
const char str_zalej         [] PROGMEM = "zalej"         ;
const char str_wyjmij_szczura[] PROGMEM = "wyjmij szczura";

const int dripStepsCount = 10;
const RecipeStep dripSteps[dripStepsCount] PROGMEM = {
  {ONSTART_TARE       , str_odmierz_kawe  , MEASURE_WEIGHT , 18 , -1 , 2 , false},
  {ONSTART_NOTHING    , str_podgrzej_wode , MEASURE_TEMP   , 85 , 10 , 2 , false},
  {ONSTART_NOTHING    , str_przygotuj_drip, PRESS_BUTTON   , -1 , -1 , -1, false},
  {ONSTART_TARE       , str_zacznij_lac   , MEASURE_WEIGHT ,  2 , -1 , 2 , true },
  {ONSTART_START_TIMER, str_preinfuzja    , MEASURE_WEIGHT , 40 , -1 , 2 , true },
  {ONSTART_NOTHING    , str_czekaj        , MEASURE_TIME   , 30 , 10 , -1, true },
  {ONSTART_NOTHING    , str_dolej         , MEASURE_WEIGHT ,150 , -1 , 10, true },
  {ONSTART_NOTHING    , str_czekaj        , MEASURE_TIME   , 90 , 10 , -1, true },
  {ONSTART_NOTHING    , str_dolej         , MEASURE_WEIGHT ,250 , -1 , 10, true },
  {ONSTART_NOTHING    , str_gotowe        , MEASURE_TIME   ,210 , 10 , -1, false}
};
const Recipe Recipe::drip = Recipe("drip", dripStepsCount, dripSteps);


const int chemexStepsCount = 8;
const RecipeStep chemexSteps[chemexStepsCount] PROGMEM = {
    {ONSTART_TARE       , str_odmierz_kawe  , MEASURE_WEIGHT , 35 , -1 , 2 , false},
    {ONSTART_NOTHING    , str_podgrzej_wode , MEASURE_TEMP   , 85 , 10 , 2 , false},
    {ONSTART_NOTHING    , str_przygotuj_chem, PRESS_BUTTON   , -1 , -1 , -1, false},
    {ONSTART_TARE       , str_zacznij_lac   , MEASURE_WEIGHT ,  2 , -1 , 2 , true },
    {ONSTART_START_TIMER, str_preinfuzja    , MEASURE_WEIGHT , 60 , -1 , 2 , true },
    {ONSTART_NOTHING    , str_czekaj        , MEASURE_TIME   , 30 , 10 , -1, true },
    {ONSTART_NOTHING    , str_dolej         , MEASURE_WEIGHT ,500 , -1 , 10, true },
    {ONSTART_NOTHING    , str_gotowe        , MEASURE_TIME   ,210 , 10 , -1, false}
};
const Recipe Recipe::chemex = Recipe("chemex", chemexStepsCount, chemexSteps);


const int fellowStepsCount = 7;
const RecipeStep fellowSteps[fellowStepsCount] PROGMEM = {
  {ONSTART_TARE       , str_odmierz_kawe  , MEASURE_WEIGHT , 20, -1,  2, false},
  {ONSTART_NOTHING    , str_podgrzej_wode , MEASURE_TEMP   , 95, 10,  2, false},
  {ONSTART_NOTHING    , str_wsyp_kawe     , PRESS_BUTTON   , -1, -1, -1, false},
  {ONSTART_TARE       , str_wlej_50g_wody , MEASURE_WEIGHT , 50, -1, 10, true },
  {ONSTART_START_TIMER, str_mieszaj       , MEASURE_TIME   , 10, 10, -1, true },
  {ONSTART_NOTHING    , str_czekaj        , MEASURE_TIME   , 70, 10, -1, true },
  {ONSTART_NOTHING    , str_wycisnij      , PRESS_BUTTON   , -1, 01, -1, false}
};
const Recipe Recipe::fellow = Recipe("fellow", fellowStepsCount, fellowSteps);


const int teaStepsCount = 2;
const RecipeStep teaSteps[teaStepsCount] PROGMEM = {
  {ONSTART_TARE       , str_zalej         , MEASURE_WEIGHT , 02  , -1,  2, false},
  {ONSTART_START_TIMER, str_wyjmij_szczura, MEASURE_TIME   , 4*60, 10, -1, false}
};
const Recipe Recipe::tea = Recipe("tea", teaStepsCount, teaSteps);

const int     Recipe::allCount = 4;
const Recipe* Recipe::all[Recipe::allCount] = { &drip, &chemex, &fellow, &tea };

//Recipe
Recipe::Recipe(char* name, int stepsCount, FlashRecipeSteps steps) {
  this->name       = name;
  this->stepsCount = stepsCount;
  this->steps      = steps;
}

bool Recipe::getStep(int i, RecipeStep *dest) {
  if (i<0 || i >= stepsCount)
    return false;
  memcpy_P(dest, &steps[i] , sizeof(RecipeStep));
  return true;
}

Recipe::~Recipe() {}

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

