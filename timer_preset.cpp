#include "timer_preset.h"

const TimerPreset TimerPreset::drip = TimerPreset(new int[4]{0, 30, 90, 180}, 4, new int[2]{20, 80}, 2);

TimerPreset::TimerPreset(int alarms[], int alarmsCount, int buzzers[], int buzzersCount) {
    this->buzzers      = buzzers     ;
    this->buzzersCount = buzzersCount;
    this->alarms       = alarms      ;
    this->alarmsCount  = alarmsCount ;
}
