#ifndef _TIME_H_
#define _TIME_H_

#include "avr/io.h"
#include "../pinout.h"

#define TIME_MAX  125 //1 ms


//Variables y Funciones

uint64_t current_time;

void time_init();

uint64_t timenow();

void delay(uint16_t ms);

//--------------------------------------
// 	Barrera

//Max escalado 8 = 65.536ms //1000= 1ms
//Max escalado 64 = 0.524s //125=1ms

#define BARRERA_ESPERA 12500 //0.1s


//Variables y Funciones

void time_init();
void esperar_moneda();


//-------------------------------------


#endif
