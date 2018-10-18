#ifndef TIMER_H_
#define TIMER_H_

#define TXT_BUFFER_COUNT 8

class Timer {
  unsigned long value = 0;
  char txtBuffer [TXT_BUFFER_COUNT];
public:
  void  setSeconds(int);
  int   getSeconds(); //returns -1 if timer is off
  void  Timer::off();
  char* getSecondsStr();
};

#endif