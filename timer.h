#ifndef TIMER_H_
#define TIMER_H_

class Timer {
  unsigned long value = 0;
public:
  void  setSeconds(int);
  int   getSeconds(); //returns -1 if timer is off
  void  Timer::off();
};

#endif