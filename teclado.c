#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

uint8_t ENABLE = 1;
uint8_t KEYPAD_IN = 0;
uint8_t ALREADY_SELECTED = 0; 

void debounceMs(int ms)
{
	cli();
// 	TCNT1 = 0;//65536-ms*(8000000/(1000*256));
// 	TIMSK1 = 0b00000001; //Habilito el contador
	
	PCMSK2 = 0b00000000; //Deshabilito las interrupciones por teclado
	delayMs(1000);
	sei();
}

void delayMs(int ms)
{
	for(int i = 0; i < ms; i++)
	{
		for(volatile int j = 0; j < 421; j++);
	}
}

// ISR(TIMER1_OVF_vect)
// {
// 	PCMSK2 = 0b00001111;
// 	TIMSK1 = 0b00000000;
// 	ENABLE = 1;
// }



void send_position(int pos)
{
	cli();
	if(ALREADY_SELECTED == 0){
		switch(pos)
		{
			case 1: PORTB = 0b00000001; break; //En el programa final en cada uno de los casos se envía la posición codificada a Jaime
			case 4: PORTB = 0b00001000; break;
			case 7: PORTB = 0b01000000; break;
			case 2: PORTB = 0b00000010; break;
			case 5: PORTB = 0b00010000; break;
			case 8: PORTB = 0b10000000; break;
			case 3: PORTB = 0b00000100; break;
			case 6: PORTB = 0b00100000; break;
			case 9: PORTB = 0b00000011; break;
		}
		ALREADY_SELECTED = 1;
	} else
	{
		if(pos == 0)
		{
			ALREADY_SELECTED = 0;
			PORTB = 0x00;
		}else
		{
			blink_led();
		}
	}
	sei();
}

void blink_led()
{
	for(volatile int i=0; i<4; i++)
	{
		PORTB = PINB | 0b00000001;
		delayMs(100);
		PORTB = PINB & 0b11111110;
		delayMs(100);
	}
}

ISR(PCINT2_vect)
{
	if(ENABLE == 1)
	{
		PORTK = 0b10000000; //Empezamos por la primera columna
		while(PORTK != 0b00001000)
		{
			delayMs(1);
			KEYPAD_IN = PINK;
			switch(KEYPAD_IN)
			{
				case 0b10001000: send_position(1); break; //En el programa final en cada uno de los casos se envía la posición codificada a Jaime
				case 0b10000100: send_position(4); break;
				case 0b10000010: send_position(7); break;
				case 0b01001000: send_position(2); break;
				case 0b01000100: send_position(5); break;
				case 0b01000010: send_position(8); break;
				case 0b00101000: send_position(3); break;
				case 0b00100100: send_position(6); break;
				case 0b00100010: send_position(9); break;
				case 0b10000001: send_position(0); break;
			}
			PORTK >>= 1;
		}
		PORTK = 0b11110000;
/*		debounceMs(2000000);*/
		ENABLE = 0;
	}
}

void setup()
{
	DDRB = 0xff; //PUERTO B SALIDA-LEDS
	DDRK = 0xf0; //Puerto K SALIDA/ENTRADA-TECLADO
	PORTB = 0X00;
	PORTK = 0b11110000; //Hay que activar todas las salidas para que cualquier tecla pueda generar la señal de interrupción

	PCICR = 0b00000100; //PCINT DEL PUERTO K
	PCMSK2 = 0b00001111; //Enable PCINT16-23

//  	TCCR1B = 0b0000100; //Preescalado 256
// 	TIMSK1 = 0b0000000;


}


int main(void)
{
	cli();
	setup();
	sei();
	while (1)
	{
	
	}
}