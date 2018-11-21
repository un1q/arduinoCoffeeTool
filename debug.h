#include "memory_free.h"

#define SerialLog(a) { Serial.print(#a); Serial.print(": "); Serial.println(a); Serial.flush(); }
#define SerialFreeMemLog() { Serial.print("Free mem: "); Serial.println(freeMemory()); Serial.flush(); }
