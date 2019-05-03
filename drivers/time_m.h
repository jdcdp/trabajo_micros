#ifndef TIME_M_H_
#define TIME_M_H_


#include "../pinout.h"

#define TIME_MAX 100 //0.1ms


uint64_t micros_total=0;

void setup_timers();

uint64_t micros();

void delay(uint8_t ms);

ISR(TIMER0_COMPA_vect);

#endif
