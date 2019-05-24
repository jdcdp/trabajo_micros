#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "motion.h"
#include "drivers/time.h"


uint8_t enable = 1; //Asociado al antirrebotes
uint8_t keypad_in = 0; //Variable que almacena el valor enmascarado del teclado
uint8_t already_selected = 0; //Variable para determinar si ya hay un producto seleccionado en proceso
uint8_t enable_blink = 0;// Variable para habilitar el parpadeo cuando se ha pulsado el teclado habiendo un producto seleccionado
uint8_t check = 1; //Para la consulta periódica
uint8_t send = 0; //Variable para enviar la posición a motores al final de la interrupción
uint8_t posicion = 0; //Variable que almacena el valor de la posicion seleccionada

//Funciones para integración

void syscall_product_out() //Se llamaría cuando el contador de vueltas haya llegado al límite establecido 
{
    	PORTB |= (1 << PB0);
    	delayMs(100);
    	PORTB &= ~(1 << PB0);
    	already_selected = 0; //Dejamos seleccionar de nuevo
	stopY();
}

void choose_again()
{
	already_selected = 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void delayMs(uint8_t ms)
{
	for(volatile uint8_t i = 0; i < ms; i++)
	{
		for(volatile uint8_t j = 0; j < 421; j++); //Cada 421 ciclos equivale a 1 ms
	}
}

void debounceMs() //Antirrebotes
{
	delayMs(8);
	enable = 1;
	PCIFR |= 0b00000001;
}

void position(int pos) //Función para almacenar el valor de la posición seleccionada y modificar valores de otras variables
{
	enable = 0;
	if(already_selected == 0)
	{
		posicion = pos;
		already_selected = 1;
		send = 1;
	}else
	{
		enable_blink = 1;
	}
}

void blink_led() //Parpadeo LED
{
	for(volatile int i=0; i<4; i++)
	{
		PORTB |= (1 << PB0);
		delayMs(100);
		PORTB &= ~(1 << PB0);
		delayMs(100);
	}
}

ISR(PCINT0_vect) //Función asociado a las interrupciones del teclado
{
	if(enable)
	{
		delayMs(1);
		PORTB = 0b10000000; //Empezamos por la primera columna
		while(PORTB != 0b00010000)
		{
			delayMs(1);
			keypad_in = PINB & 0b11111100; //Enmascaro
			switch(keypad_in)
			{
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
		delayMs(1);
		PORTB = 0b11100000;
		if(send == 1)
		{
			selectProduct(posicion); //Enviamos la posición a los motores
			send = 0;
		}
		debounceMs(); 
	}
}

ISR(INT3_vect) //Piezo eléctrico, nos permite volver a enviar una posición a motores
{
	already_selected = 0;
}

void setup_teclado()
{
	DDRB |= 0b11100001; //Puerto B SALIDA/ENTRADA-TECLADO
	PORTB |= 0b11100000; //Hay que activar todas las salidas para que cualquier tecla pueda generar la señal de interrupción
	DDRD &= ~(1 << DDD3);

	PCICR |= 0b00000001; //PCINT DEL PUERTO B
	PCMSK0 |= 0b00011100; //Enable PCINT0-7

	EICRA |= (1 << ISC31); //Flanco de bajada para el piezoeléctrico
	EIMSK |= (1 << INT3);

}

