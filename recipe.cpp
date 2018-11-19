#include "recipe.h"
#include "globals.h"
#include "sensor_alarm.h"
#include "action_melody.h"
#include "memory_free.h"

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
    RecipeStep(ONSTART_TARE       , str_odmierz_kawe  , MEASURE_WEIGHT , 18 , -1 , false, 0 , false),
    RecipeStep(ONSTART_NOTHING    , str_podgrzej_wode , MEASURE_TEMP   , 85 , 75 , true , 0 , false),
    RecipeStep(ONSTART_NOTHING    , str_przygotuj_drip, PRESS_BUTTON   , -1 , -1 , false, -1, false),
    RecipeStep(ONSTART_TARE       , str_zacznij_lac   , MEASURE_WEIGHT , 2  , -1 , false, 5 , true ),
    RecipeStep(ONSTART_START_TIMER, str_preinfuzja    , MEASURE_WEIGHT , 40 , -1 , false, 0 , true ),
    RecipeStep(ONSTART_NOTHING    , str_czekaj        , MEASURE_TIME   , 30 , 20 , true , -1, true ),
    RecipeStep(ONSTART_NOTHING    , str_dolej         , MEASURE_WEIGHT , 150, -1 , false, 10, true ),
    RecipeStep(ONSTART_NOTHING    , str_czekaj        , MEASURE_TIME   , 90 , 80 , true , -1, true ),
    RecipeStep(ONSTART_NOTHING    , str_dolej         , MEASURE_WEIGHT , 250, -1 , false, 10, true ),
    RecipeStep(ONSTART_NOTHING    , str_gotowe        , MEASURE_TIME   , 210, 200, true , -1, false)
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

RecipeStep::RecipeStep(OnStart onStart, FlashAddr text, SensorType sensorType, int value, int buzzValue, bool buzz, int timeoutIfNoSensor, bool autoNext) {
  this->onStart           = onStart          ;
  this->text              = text             ;
  this->buzz              = buzz             ;
  this->sensorType        = sensorType       ;
  this->value             = value            ;
  this->buzzValue         = buzzValue        ;
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

//FollowRecipe

FollowRecipe::FollowRecipe() {}

FollowRecipe::~FollowRecipe() {
  deleteAlarm();
}


void FollowRecipe::prepare(const Recipe *recipe){
  this->recipe = recipe;
  this->step   = -1;
}

void FollowRecipe::start(){
  this->step   = -1;
  foreward();
}

void FollowRecipe::stop(){
  this->recipe = nullptr;
  this->step   = -1;
}

void FollowRecipe::deleteAlarm(){
  if (alarm)
    delete(alarm);
  alarm = nullptr;
  alarmDesc.emptyString();
}
  
void FollowRecipe::foreward(){
  if (recipe == nullptr || step >= recipe->stepsCount-1 || step < -1) 
    return;
  step++;
  deleteAlarm();
  RecipeStep* s = getStep();
  if (!s)
    return;
  Sensor* sensor       = s->getSensor();
  bool    sensorActive = sensor && sensor->active();
  if (sensorActive) {
    alarm = new SensorAlarm(&alarmAction, s->buzz ? &buzzAction : nullptr, sensor, s->value, s->buzzValue, s->getAlarmMode());
    switch(s->sensorType) {
      case MEASURE_WEIGHT: alarmDesc.weightToString(alarm->alarmValue) ; break;
      case MEASURE_TEMP  : alarmDesc.tempToString(alarm->alarmValue)   ; break;
      case MEASURE_TIME  : alarmDesc.secondsToString(alarm->alarmValue); break;
      case PRESS_BUTTON  : alarmDesc.flashToString(F("press button"))  ; break;
    }
  } else if (s->timeoutIfNoSensor > 0) {
    alarm = new SensorAlarm(&timeoutAction, nullptr, &measureTimeout, s->timeoutIfNoSensor, -1);
    measureTimeout.start();
    alarmDesc.flashToString(F("wait or skip"));
  } else if (s->timeoutIfNoSensor < 0) {
    alarmDesc.flashToString(F("skip manually"));
  }
  if ( s->onStart == ONSTART_TARE ) {
    measureWeight.tare();
  } else if( s->onStart == ONSTART_START_TIMER ) {
    measureTime.start();
  }
  if (!sensorActive && s->timeoutIfNoSensor == 0)
    foreward();
}

void FollowRecipe::backward(){
  if (recipe == nullptr)
    return;
  if (step > 0)
    step--;
}

bool FollowRecipe::check() {
  RecipeStep* s = getStep();
  bool result = !alarm || alarm->check();
  if (result && s && s->autoNext)
    foreward();
  return result;
}

char* FollowRecipe::getText(StringBuffer *buffer) {
  RecipeStep* s = getStep();
  return s ? buffer->flashToString(s->text) : nullptr;
}

char* FollowRecipe::getTextNext(StringBuffer *buffer) {
  int step = this->step + 1;
  if (!recipe || step < 0 || step >= recipe->stepsCount)
    return nullptr;
  return buffer->flashToString(recipe->steps[step].text);
}

RecipeStep* FollowRecipe::getStep() {
  if (recipe == nullptr || step < 0 || step >= recipe->stepsCount )
    return nullptr;
  return &recipe->steps[step];
}

SensorAlarm* FollowRecipe::getAlarm() {
  return alarm;
}