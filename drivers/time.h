#ifndef _TIME_H_
#define _TIME_H_

#include "avr/io.h"
#include "../pinout.h"

//Registros Timer 0
#define TIME_MAX  100 //0.1ms

#define TIME_TCCRA TCCR0A
#define TIME_OCRA  OCR0A

#define TIME_TIMSK  TIMSK0   
#define TIME_TCCRB TCCR0B

//Variables y Funciones
uint64_t current_time;

void init_time();

uint64_t timenow();

void delay(uint16_t ms);

ISR(TIMER0_COMPA_vect);

#endif
