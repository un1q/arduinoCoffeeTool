#include "multi_alarm.h"
#include <limits.h>

void MultiAlarm::reset() {
  for (int i=0; i<alarmsCount; i++) {
    alarms[i].reset();
  }
}

bool MultiAlarm::check(int value) {
  bool result = false;
  for (int i=0; i<alarmsCount; i++) {
    result = result | alarms[i].check(value);
  }
  return result;
}

int MultiAlarm::difference(int value) {
  int result = INT_MIN;
  for (int i=0; i<alarmsCount; i++) {
    int d = alarms[i].difference(value);
    if (d < 0 && d > result)
      result = d;
  }
  return result == INT_MIN ? 0 : result;
}

Alarm* MultiAlarm::getNext(int value) {
  Alarm* alarm = nullptr;
  int v = INT_MIN;
  for (int i=0; i<alarmsCount; i++) {
    int d = alarms[i].difference(value);
    if (d < 0 && d > v) {
      v = d;
      alarm = &alarms[i];
    }
  }
  return alarm;
}
