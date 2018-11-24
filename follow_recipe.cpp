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
#define NEW_F_STRING_BUFFER_PLUS(strBufPointer, str, plus) strBufPointer = new StringBuffer(sizeof(str)+plus); strBufPointer->flashToString(F(str));

void FollowRecipe::update() {
  RecipeStep actualStep;
  clean();
  if (recipe == nullptr || !recipe->getStep(stepNr, &actualStep)) {
    stepNr = -1;
    return;
  }
  autoNext = actualStep.autoNext;
  Sensor* sensor = actualStep.getSensor();
  sensorActive = sensor && sensor->active();
  switch(actualStep.sensorType) {
    case MEASURE_TEMP  : alarmDescBuffer = new StringBuffer(tempStringLength   + 4); alarmDescBuffer->tempToString   (actualStep.value); break;
    case MEASURE_WEIGHT: alarmDescBuffer = new StringBuffer(weightStringLength + 4); alarmDescBuffer->weightToString (actualStep.value); break;
    case MEASURE_TIME  : alarmDescBuffer = new StringBuffer(timeStringLength   + 4); alarmDescBuffer->secondsToString(actualStep.value); break;
    default: NEW_F_STRING_BUFFER_PLUS(alarmDescBuffer, "---", 4); break;
  }
  if (sensorActive) {
    alarm = new SensorAlarm(&alarmAction, sensor, actualStep.value, actualStep.buzzMargin, actualStep.getAlarmMode());
  } else if (actualStep.timeoutIfNoSensor > 0) {
    alarm = new SensorAlarm(nullptr, &measureTimeout, actualStep.timeoutIfNoSensor, -1, Alarm::crossingUp);
    autoNext = true;
    measureTimeout.start();
//    NEW_F_STRING_BUFFER(alarmDescBuffer, "wait or skip");
//  } else {
//    NEW_F_STRING_BUFFER(alarmDescBuffer, "skip manually");
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

#undef NEW_F_STRING_BUFFER
#undef NEW_F_STRING_BUFFER_PLUS

bool FollowRecipe::check() {
  if (stepNr < 0)
    return false;
  if ((!alarm || alarm->check()) && autoNext) {
    foreward();
    return true;
  }
  return false;
}

char* FollowRecipe::getAlarmDesc() {
  if (!alarmDescBuffer)
    return nullptr;
  char* str = alarmDescBuffer->get();
  int i = alarmDescBuffer->getSize() - 5;
  if (sensorActive || i <= 0)
    return str;
  str[i++] = ' ';
  str[i++] = '[';
  str[i++] = alarm == nullptr ? 'X' : '0'+min(9, alarm->remains());
  str[i++] = ']';
  str[i]   = '\0';
  return str;
}
