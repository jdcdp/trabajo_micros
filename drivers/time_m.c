#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "time_m.h"

/*
void init_timers(){
	//TO DO
	//Inicializar timer para delays de duracion F_CPU/1000000L
}*/



int micros(){
	return micros_total;
}

void delays(uint8_t ms){
	
	sei();
	int end_time=micros()+ms*10;
	while (micros()<end_time);//change with an interruption and HOLD()
 
}




ISR(TIMER0_COMPA_vect){
	++micros_total;
}

void setup_time(){
	cli();
	
	TIME_TCCRnA =0x02; //Modo CTC
	
	TIME_OCRnA =TIME_MAX; //Set timer TOP_A	

	TIME_TCCRnB=0x01; //Preescalado de 0, cuenta cada us (1MHz)

	TIMSK0 |= (1 << OCIE0A); //Enable Interrupt from CTC_A
	
	sei();
}

