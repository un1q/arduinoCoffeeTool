#include "multi_alarm.h"

bool MultiAlarm::check(int value) {
  bool result = false;
  for (int i=0; i<alarmsCount; i++) {
    result = result | alarms[i].check(value);
  }
  return result;
}
