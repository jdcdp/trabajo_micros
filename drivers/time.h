#ifndef _TIME_H_
#define _TIME_H_

#include "avr/io.h"
#include "../pinout.h"

//Registros Timer 0
#define TIME_MAX 100 //0.1ms

#define TIME_TCCRnA TCCR0A
#define TIME_OCRnA OCR0A

#define TIME_TCCRnB TCCR0B

//Variables y Funciones
uint64_t current_time;

void init_time();

uint64_t timenow();

void delay(uint16_t ms);

ISR(TIMER0_COMPA_vect);

#endif
