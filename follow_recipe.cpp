#include "follow_recipe.h"
#include "globals.h"

FollowRecipe::FollowRecipe() {}

FollowRecipe::~FollowRecipe() {
  deleteAlarm();
}


void FollowRecipe::prepare(const Recipe *recipe){
  this->recipe = recipe;
  this->stepNr   = -1;
}

void FollowRecipe::start(){
  this->stepNr = -1;
  foreward();
}

void FollowRecipe::stop(){
  this->recipe = nullptr;
  this->stepNr   = -1;
}

void FollowRecipe::deleteAlarm(){
  if (alarm)
    delete(alarm);
  alarm = nullptr;
  alarmDesc.emptyString();
}
  
void FollowRecipe::foreward(){
  if (recipe == nullptr || stepNr >= recipe->stepsCount-1 || stepNr < -1) 
    return;
  stepNr++;
  update();
}

void FollowRecipe::backward(){
  if (recipe == nullptr)
    return;
  if (stepNr > 0)
    stepNr--;
  update();
}

void FollowRecipe::update() {
  deleteAlarm();
  RecipeStep* s = getStep();
  if (!s)
    return;
  isTimeout = false;
  Sensor* sensor       = s->getSensor();
  bool    sensorActive = sensor && sensor->active();
  if (sensorActive) {
    alarm = new SensorAlarm(&alarmAction, sensor, s->value, s->buzzMargin, s->getAlarmMode());
    switch(s->sensorType) {
      case MEASURE_WEIGHT: alarmDesc.weightToString(alarm->alarmValue) ; break;
      case MEASURE_TEMP  : alarmDesc.tempToString(alarm->alarmValue)   ; break;
      case MEASURE_TIME  : alarmDesc.secondsToString(alarm->alarmValue); break;
      case PRESS_BUTTON  : alarmDesc.flashToString(F("press button"))  ; break;
    }
  } else if (s->timeoutIfNoSensor > 0) {
    alarm = new SensorAlarm(nullptr, &measureTimeout, s->timeoutIfNoSensor, -1, Alarm::crossingUp);
    isTimeout = true;
    measureTimeout.start();
    alarmDesc.flashToString(F("wait or skip"));
  } else {
    alarmDesc.flashToString(F("skip manually"));
  }
  alarmDesc.center();
  if ( s->onStart == ONSTART_TARE ) {
    measureWeight.tare();
  } else if( s->onStart == ONSTART_START_TIMER ) {
    measureTime.start();
    timerStartMelody.play();
  }
}

bool FollowRecipe::check() {
  RecipeStep* s = getStep();
  bool result = !alarm || alarm->check();
  if (result && s && (s->autoNext || isTimeout))
    foreward();
  return result;
}

char* FollowRecipe::getText(StringBuffer *buffer) {
  RecipeStep* s = getStep();
  return s ? buffer->flashToString(s->text) : nullptr;
}

char* FollowRecipe::getTextNext(StringBuffer *buffer) {
  RecipeStep nextStep;
  if (recipe == nullptr || !recipe->getStep(stepNr+1, &nextStep))
    return nullptr;
  return buffer->flashToString(nextStep.text);
}

RecipeStep* FollowRecipe::getStep() {
  if (recipe == nullptr || !recipe->getStep(stepNr, &actualStep))
    return nullptr;
  return &actualStep;
}

SensorAlarm* FollowRecipe::getAlarm() {
  return alarm;
}