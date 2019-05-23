#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "time.h"

void setup_time(){

        cli();

	current_time=0;

        TIME_TCCRA = 0x02; //Modo CTC

        TIME_OCRA = TIME_MAX; //Set timer TOP_A

        TIME_TCCRB = 0x03; //Preescalado de 64, cuenta cada 8 us (8MHz)

        TIME_TIMSK |= (1 << OCIE0A); //Enable Interrupt from CTC_A

//----------------------------------------------------------------------------
//				Barrera:

	BARRERA_TCCRB |= (1<<WGM32); //Modo CTC 
	BARRERA_TCCRB |= (1<<CS31)|(1<<CS30); //Con preescalado 64, cuenta cada 8us (8MHz)

//----------------------------------------------------------------------------

        sei();
}

uint64_t timenow(){
	return current_time;
}

void delay(uint16_t ms){

	volatile uint16_t end_time=timenow()+ms;
	sei();
	while (timenow()<end_time);
}


ISR(TIMER0_COMPA_vect){
	current_time++;
}

//----------------------------------------------------------------------------
//			Barrera

void esperar_moneda(){ //Espera a que pase la moneda para cerrar la barrera

	BARRERA_TIMSK |= (1 << OCIE3A); //Poner interrupcion de CTC_A
	BARRERA_OCRA = BARRERA_CNT + BARRERA_ESPERA ; //Set timer TOP_A;
	
	TIFR3= (1 << OCIE3A); //Quitar posible bandera de interrupcion que haya saltado
	
}

ISR(TIMER3_COMPA_vect){ //Solo para esperar a la moneda

	//Quitar interrupcion de CTC_A
	BARRERA_TIMSK &= ~(1 << OCIE3A);

	cerrar_barrera();

}
