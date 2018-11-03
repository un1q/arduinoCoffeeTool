#ifndef ALARM_TIMER_H_
#define ALARM_TIMER_H_

// Setting and checking timer alarm.
// Alarm can be complex, for example:
// play melody after 30,90 and 120 seconds and buzz 10 seconds before each alarm

#include "melody.h"
#include "multi_alarm.h"
#include "measure_time.h"
#include "action_melody.h"
#include "string_buffer.h"

class AlarmTimer {
    MultiAlarm   multiAlarm;
    MultiAlarm   multiAlarmBuzz;
    MultiAlarm   multiAlarmMusic;
    ActionMelody *playMelody;
    ActionMelody *playBuzz;
    bool         isOn = false;
    StringBuffer stringBuffer;
  public:
    MeasureTime  *measureTime;
    
    AlarmTimer(MeasureTime *measureTime, Melody *melody, Melody *buzz);
    ~AlarmTimer();
    void  loop();
    void  startDrip();
    void  stop();
    int   getSecondsTotal();
    char* toString();
};

#endif