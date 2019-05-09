#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "motion.h"
#include "pinout.h"
#include "main.h"

//Variables

uint8_t enable = 1; //Asociado al antirrebotes
uint8_t keypad_in = 0; //Variable que almacena el valor enmascarado del teclado
uint8_t already_selected = 0; //Variable para determinar si ya hay un producto seleccionado en proceso

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Funciones para integración

void nothing_selected()
{
	already_selected = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Funciones ha sustituir

void debounceMs() //Hay que sustituirlo por el de uso común
{
	cli();
	TCNT1 = 65536-8*(8000000/1000*256);
	TIMSK1 |= (1<<TOIE1); //Habilito el contador
	sei();
}

ISR(TIMER1_OVF_vect)//Hay que sustituirlo por el de uso común
{
	TIMSK1 = 0x00;
	PCIFR |= 0b00000001; //Bajo la bandera del registro de las interrupciones por si acaso
	enable = 1; //Fin de los rebotes
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Funciones finales

void delayMs(int ms)
{
	for(volatile int i = 0; i < ms; i++){
		for(volatile int j = 0; j < 421; j++);
	}
}

void position(int pos)// De aquí se envía la posición ha Jaime
{
	if(already_selected == 0){
		already_selected = 1;
		selectProduct(pos); //Envio posición a Jaime	
	} 
	else{
			blink_led();
	}
}

void blink_led() //Función que hace parpadear el led en caso de pulsar el teclado un producto ya seleccionado
{
	for(volatile int i=0; i<4; i++){
		PORTB |= (1 << PB0);
		delayMs(100);
		PORTB = 0b11111110 & PINB;
		delayMs(100);
	}
}

ISR(KEYPAD) //Función asociado a las interrupciones del teclado
{
	if(enable){
		enable = 0;
		PORTB = 0b10000000; //Empezamos por la primera columna
		while(PORTB != 0b00010000){
			delayMs(1);
			keypad_in = PINB & 0b11111100; //Enmascaro
			switch(keypad_in){
				case 0b10010000: position(1); break;
				case 0b10001000: position(2); break;
				case 0b10000100: position(3); break;
				case 0b01010000: position(4); break;
				case 0b01001000: position(5); break;
				case 0b01000100: position(6); break;
				case 0b00110000: position(7); break;
				case 0b00101000: position(8); break;
				case 0b00100100: position(9); break;
			}
			PORTB >>= 1;
		}
		PORTB = 0b11100000;
		debounceMs(); //Cambiar en función de la función común de antirrebotes
	}
}

ISR (PIEZO)
{
	change_choque();
}

void setup_teclado()
{
	DDRB = 0b11100001; //Puerto K SALIDA/ENTRADA-TECLADO
	PORTB = 0b11100001; //Hay que activar todas las salidas para que cualquier tecla pueda generar la señal de interrupción

	PCICR = 0b00000001; //PCINT DEL PUERTO B
	PCMSK0 = 0b00011100; //Enable PCINT0-7
//Cambiar
	TCCR1B |= (1<<CS12);  //Preescalado 256
	TCNT1 = 65536-8*(8000000/1000*256);
	TIMSK1 = 0x00;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
