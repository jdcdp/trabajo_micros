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
	//Modo CTC
	BARRERA_TCCRB |= (1<<WGM32);

	//Tiempos necesarios de espera
	BARRERA_OCRA = BARRERA_ESPERA; //Set timer TOP_A; 8000 es 1ms

	BARRERA_TCCRB |= (1<<WGM32); //Modo CTC 
	BARRERA_TCCRB |= (1<<CS31)|(1<<CS30); //Con preescalado 64, cuenta cada 8us (8MHz)

//----------------------------------------------------------------------------

        sei();
}

uint64_t timenow(){
	return current_time;
}

void delay(uint16_t ms){

	sei();
	volatile uint16_t end_time=timenow()+ms;
	while (timenow()<end_time);
}


ISR(TIMER0_COMPA_vect){
	current_time++;
}

//----------------------------------------------------------------------------
//			Barrera

void esperar_moneda(){ //Espera a que pase la moneda para cerrar la barrera

	//Tiempos necesarios de espera
	//MIRAR SI ES UNISiGNED INT O NO PARA PONER TIPO EN LA OPERACION
	BARRERA_OCRA = BARRERA_CNT + BARRERA_ESPERA ; //Set timer TOP_A;
	BARRERA_TIMSK |= (1 << OCIE3A); //Poner interrupcion de CTC_A

	//PORTB= ~PINB; //PRUEBAS
}

ISR(TIMER3_COMPA_vect){ //Solo para esperar a la moneda

	//Quitar interrupcion de CTC_A
	BARRERA_TIMSK &= ~(1 << OCIE3A);

	cerrar_barrera();

//----------------------------------------------------------------------------

}
