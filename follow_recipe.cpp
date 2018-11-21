#include "follow_recipe.h"
#include "globals.h"

FollowRecipe::FollowRecipe() {}

FollowRecipe::~FollowRecipe() {
  clean();
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

void FollowRecipe::clean(){
  if (alarm)
    delete(alarm);
  alarm = nullptr;
  
  if (alarmDescBuffer);
    delete(alarmDescBuffer);
  alarmDescBuffer = nullptr;
  
  if (textBuffer);
    delete(textBuffer);
  textBuffer = nullptr;
  
  if (nextTextBuffer);
    delete(nextTextBuffer);
  nextTextBuffer = nullptr;
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

#define NEW_F_STRING_BUFFER(strBufPointer, str) strBufPointer = new StringBuffer(sizeof(str)); strBufPointer->flashToString(F(str));

void FollowRecipe::update() {
  clean();
  if (recipe == nullptr || !recipe->getStep(stepNr, &actualStep)) {
    stepNr = -1;
    return;
  }
  isTimeout = false;
  Sensor* sensor       = actualStep.getSensor();
  bool    sensorActive = sensor && sensor->active();
  if (sensorActive) {
    alarm = new SensorAlarm(&alarmAction, sensor, actualStep.value, actualStep.buzzMargin, actualStep.getAlarmMode());
    switch(actualStep.sensorType) {
      case MEASURE_TEMP  : alarmDescBuffer = new StringBuffer(tempStringLength   ); alarmDescBuffer->tempToString(alarm->alarmValue)   ; break;
      case MEASURE_WEIGHT: alarmDescBuffer = new StringBuffer(weightStringLength ); alarmDescBuffer->weightToString(alarm->alarmValue) ; break;
      case MEASURE_TIME  : alarmDescBuffer = new StringBuffer(timeStringLength   ); alarmDescBuffer->secondsToString(alarm->alarmValue); break;
      case PRESS_BUTTON  : NEW_F_STRING_BUFFER(alarmDescBuffer, "press button"); break;
    }
  } else if (actualStep.timeoutIfNoSensor > 0) {
    alarm = new SensorAlarm(nullptr, &measureTimeout, actualStep.timeoutIfNoSensor, -1, Alarm::crossingUp);
    isTimeout = true;
    measureTimeout.start();
    NEW_F_STRING_BUFFER(alarmDescBuffer, "wait or skip");
  } else {
    NEW_F_STRING_BUFFER(alarmDescBuffer, "skip manually");
  }
  if ( actualStep.onStart == ONSTART_TARE ) {
    measureWeight.tare();
  } else if( actualStep.onStart == ONSTART_START_TIMER ) {
    measureTime.start();
    timerStartMelody.play();
  }
  textBuffer = new StringBuffer((FlashAddr)actualStep.text);
  RecipeStep nextStep;
  if (recipe->getStep(stepNr+1, &nextStep))
    nextTextBuffer = new StringBuffer((FlashAddr)nextStep.text);
}

bool FollowRecipe::check() {
  if (stepNr < 0)
    return false;
  bool result = !alarm || alarm->check();
  if (result && (actualStep.autoNext || isTimeout))
    foreward();
  return result;
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

SensorAlarm* FollowRecipe::getAlarm() {
  return alarm;
}