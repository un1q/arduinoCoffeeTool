#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "lcd_N5110.h"
#include "keyboard.h"
#include "measure_weight.h"
#include "measure_temperature.h"
#include "measure_time.h"

extern Lcd                *lcd          ;
extern Keyboard           keyboard      ;
extern MeasureWeight      measureWeight ;
extern MeasureTemperature measureTemp   ;
extern MeasureTime        measureTime   ;

#endif