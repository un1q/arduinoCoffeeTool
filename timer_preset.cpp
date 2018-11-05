#include "timer_preset.h"

const TimerPreset TimerPreset::drip   = TimerPreset(-2, " drip", new int[4]{0, 30, 90, 180}, 4, new int[2]{20, 80}, 2);
const TimerPreset TimerPreset::chemex = TimerPreset(-2, "chmex", new int[3]{0, 30, 180}, 3, new int[1]{20}, 1);
const TimerPreset TimerPreset::tea    = TimerPreset( 0, "  tea", new int[1]{4*60}, 1);

TimerPreset::TimerPreset(int startAt, char* name, int alarms[], int alarmsCount) 
  : TimerPreset(startAt, name, alarms, alarmsCount, nullptr, 0) {}

TimerPreset::TimerPreset(int startAt, char* name, int alarms[], int alarmsCount, int buzzers[], int buzzersCount) {
    this->buzzers      = buzzers     ;
    this->buzzersCount = buzzersCount;
    this->alarms       = alarms      ;
    this->alarmsCount  = alarmsCount ;
    this->name         = name        ;
    this->startAt      = startAt     ;
}
