#ifndef TIMER_H_
#define TIMER_H_

// Simple timer class
// It can has many alarms in row, for example: 30 sec, then 90 sec, then 120 sec
// Use getSeconds() to check if alarm should be activated,
// Then use nextAlarm() to switch into next alarm

class Timer {
  unsigned long *alarms;
  int           alarmsCount  = 0;
  int           currentAlarm = -1;
public:
  void  setSeconds(int);
  int   getSeconds(); //returns -1 if timer is off, returns 0 if alarm should be activated
  void  setSeconds(int*, int); //set many alarms
  void  off();
  bool  isOn();
  bool  nextAlarm(); //returns true if next alarm exists
};

#endif