#ifndef _TIME_H_
#define _TIME_H_

#include "avr/io.h"
#include "../pinout.h"

//Registros Timer 0

#define TIME_MAX  125 //1 ms

#define TIME_TCCRA TCCR0A
#define TIME_OCRA  OCR0A

#define TIME_TIMSK  TIMSK0   
#define TIME_TCCRB TCCR0B

//Variables y Funciones
uint64_t current_time;

void time_init();

uint64_t timenow();

void delay(uint16_t ms);

ISR(TIMER0_COMPA_vect);


//Registros Timer Barrera

//Max escalado 8 = 65.536ms //1000= 1ms
//Max escalado 64 = 0.524s //125=1ms  

#define BARRERA_ESPERA 12500 //0.1s

#define BARRERA_TCCRB TCCR3B

#define BARRERA_OCRA  OCR3A

#define BARRERA_CNT	TCNT3

#define BARRERA_TIMSK  TIMSK3


//Variables y Funciones

void time_init();
void esperar_moneda();

ISR(TIMER3_COMPA_vect);
ISR(TIMER3_COMPB_vect);


#endif
