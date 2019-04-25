#ifndef __TIME_M__
#define __TIME_M__
#include "time_m.c"

uint64_t micros_total=0;

void init_timers();

void micros();

void delay(uint8_t ms);


#endif
