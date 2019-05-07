
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "time.h"

void init_time(){
        cli();

	current_time=0;

        TIME_TCCRA = 0x02; //Modo CTC

        TIME_OCRA = TIME_MAX; //Set timer TOP_A

        TIME_TCCRB = 0x01; //Preescalado de 0, cuenta cada us (1MHz)

        TIME_TIMSK |= (1 << OCIE0A); //Enable Interrupt from CTC_A

        sei();
}

uint64_t timenow(){
	return current_time;
}

void delay(uint16_t ms){

	sei();
	uint16_t end_time=timenow()+ms*10;
	while (timenow()<end_time);//Use a timer instead
}


ISR(TIMER0_COMPA_vect){
	current_time++;
}


