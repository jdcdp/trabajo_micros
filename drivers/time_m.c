
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "time_m.h"

void setup_time(){
        cli();

        TIME_TCCRA = 0x02; //Modo CTC

        TIME_OCR = TIME_MAX; //Set timer TOP_A

        TIME_TCCRB = 0x01; //Preescalado de 0, cuenta cada us (1MHz)

        TIMSK0 |= (1 << OCIE0A); //Enable Interrupt from CTC_A

        sei();
}

uint64_t micros(){
	return micros_total;
}

void delay(uint8_t ms){

	sei();
	int end_time=micros()+ms*10;
	while (micros()<end_time);//maybe change to an interruption and use HOLD()

}


ISR(TIMER0_COMPA_vect){
	++micros_total;
}


