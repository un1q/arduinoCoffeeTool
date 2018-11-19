#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "lcd_N5110.h"
#include "keyboard.h"
#include "measure_weight.h"
#include "measure_temperature.h"
#include "measure_time.h"
#include "melody.h"
#include "action_melody.h"

extern Lcd                *lcd          ;
extern Keyboard           keyboard      ;
extern MeasureWeight      measureWeight ;
extern MeasureTemperature measureTemp   ;
extern MeasureTime        measureTime   ;
extern Melody             alarmMelody   ;
//extern Melody             buzzMelody    ;
extern ActionMelody       alarmAction   ;
//extern ActionMelody       buzzAction    ;
extern ActionMelody       timeoutAction ;
extern MeasureTime        measureTimeout;


#endif