#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "motion.h"


uint8_t enable = 1; //Asociado al antirrebotes
uint8_t keypad_in = 0; //Variable que almacena el valor enmascarado del teclado
uint8_t already_selected = 0; //Variable para determinar si ya hay un producto seleccionado en proceso
uint8_t enable_blink = 0;
uint8_t check = 1; //Para la consulta periódica


//Funciones para integración

void select_again() //Se llamaría cuando el contador de vueltas haya llegado al límite establecido (o cuando hay dinero de más??Guille)
{
    PORTB |= (1 << PB0);
	delayMs(100);
	PORTB &= ~(1 << PB0);
	already_selected = 0; //Dejamos seleccionar de nuevo
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void debounceMs() //Hay que sustituirlo por el de uso común
{
	delayMs(8);
	enable = 1;
	PCIFR |= 0b00000001;
}

void delayMs(int ms)
{
	for(volatile int i = 0; i < ms; i++)
	{
		for(volatile int j = 0; j < 421; j++);
	}
}


ISR(TIMER1_OVF_vect)//Sustituible, es necesario una función de consulta periódica
{
	check = 1;
}


void position(int pos)
{
	enable = 0;
	if(already_selected == 0)
	{
		selectProduct(pos); //Envio posición a Jaime
		already_selected = 1;
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
		debounceMs(); //Cambiar en función de la función común de antirrebotes
	}
}

ISR(INT3_vect) //Piezo eléctrico
{
	already_selected = 0;
}

void setup_teclado()
{
	DDRB = 0b11100001; //Puerto B SALIDA/ENTRADA-TECLADO
	PORTB = 0b11100000; //Hay que activar todas las salidas para que cualquier tecla pueda generar la señal de interrupción
	DDRD &= ~(1 << DDD3);

	PCICR = 0b00000001; //PCINT DEL PUERTO B
	PCMSK0 = 0b00011100; //Enable PCINT0-7
	PCIFR |= 0b00000001;

	EICRA |= (1 << ISC31);
	EIMSK |= (1 << INT3);

 	TCCR1B |= (1<<CS12);  //Preescalado 256
 	TCNT1 = 65536-2*(8000000/256);
 	TIMSK1 |= (1<<TOIE1);
}




/*int main(void) //EJEMPLO DE POSIBLE CONSULTA PERIÓDICA
{
	cli();
	setup_teclado();
	sei();
	while (1)
	{
 		if(check)
 		{
			if(enable_blink)
			{
 			blink_led();
			enable_blink = 0;
 			}
 		}
	}
}*/
