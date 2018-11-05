#ifndef ALARM_TIMER_H_
#define ALARM_TIMER_H_

// Setting and checking timer alarm.
// Alarm can be complex, for example:
// play melody after 30,90 and 120 seconds and buzz 10 seconds before each alarm

#include "multi_alarm.h"
#include "measure_time.h"
#include "timer_preset.h"
#include "action.h"
#include "string_buffer.h"

class AlarmTimer {
    bool         on           = false;
    StringBuffer stringBuffer;
    MultiAlarm   *multiAlarm  = nullptr;
    Action       *alarmAction = nullptr;
    Action       *buzzAction  = nullptr;
    char*        name         = nullptr;
    int          startAt      = 0;
    
    void destroyMultiAlarm();
  public:
    MeasureTime  *measureTime;
    
    AlarmTimer(MeasureTime *measureTime, TimerPreset *preset, Action *alarmAction, Action *buzzAction);
    ~AlarmTimer();
    bool  isOn();
    void  loop();
    void  start();
    void  stop();
    int   getSecondsTotal();
    char* toString();
    void  usePreset(TimerPreset *timerPreset);
};

#endif