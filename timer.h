#ifndef TIMER_H_
#define TIMER_H_

class Timer {
  unsigned long *alarms;
  int           alarmsCount  = 0;
  int           currentAlarm = -1;
public:
  void  setSeconds(int);
  int   getSeconds(); //returns -1 if timer is off
  void  setSeconds(int*, int); //set mamy alarms
  void  off();
  bool  isOn();
  bool  nextAlarm(); //returns true if next alarm exists
};

#endif