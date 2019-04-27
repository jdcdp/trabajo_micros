#ifndef TIME_M_H_
#define TIME_M_H_


#include "pinout.h"

#define TIME_MAX 100 //0.1ms



//Borrar ya que esta incluido en pinout.h
#define TIME_TCCR       TCCR0A
#define TIME_OCR        OCR0A
#define TIME_TCCR       TCCR0B


uint64_t micros_total=0;

void setup_timers();

void micros();

void delay(uint8_t ms);

ISR(TIMER0_COMPA_vect);

#endif
