/*
 * GccApplication2.c
 *
 * Created: 09/04/2019 17:47:08
 * Author : Admin
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "pruebas_monedero.h"

uint16_t ta,tb;
float relacion;
uint8_t ultima_moneda;
float saldo;


int tipo_moneda(float relacion){
	
	if((relacion > C10MIN) && (relacion < C10MAX)){
		saldo+=0.10;
		return 1; //10 cent
	}
	else if((relacion > C20MIN) && (relacion < C20MAX)){
		saldo+=0.20;
		return 2; //20 cent
	}
	else if((relacion > C50MIN) && (relacion < C50MAX)){
		saldo+=0.50;
		return 3; //50 cent
	}
	else if((relacion > E1MIN) && (relacion < E1MAX)){
		saldo+=1;
		return 4; //1 euro
	}
	else {
		return 0; //No reconocida
	}
	
}

//Sensor Optico 1
ISR(TIMER4_CAPT_vect){
	if((PINL & 0x01) != 0){ //Flanco Subida
		//Arrancar Contadores Modo Normal (Bit0 =1) y...
		//setBit(TCCR4B, 6);
		TCCR4B=0x02; //Hacer que capture con flanco de bajada de S01 (Bit6=0)
		TCCR5B=0x42; //Flanco subida de S02(Bit6=1)

		
	}
	
	if((PINL & 0x01) == 0){ //Flanco Subida
		
		//Determinacion tipo de moneda
		ta=(uint16_t)ICR4;
		tb=(uint16_t)ICR5; //Estoy suponiendo que el SO2 siempre se activa antes que se desactiva el S01
		
		relacion=(float)ta/tb;
		ultima_moneda= tipo_moneda(relacion);
		

		//Parar timers y ...
		TCCR4B=0x40; //Hacer que capture con flanco de subida de S01 (Bit6=1)
		TCCR5B=0x40; //Hacer que capture por flanco de subida de S02 (Bit6=1)
		
		//Resetear Timers
		TCNT4=0x00;
		TCNT5=0x00;	
	}
}

void setup(){
	
	//Configuracion I/O
	DDRL=0x00; //Entradas, mas tarde hacer por mascara o lo que sea

	//Timers para Input Capture
	cli();
	
	TIMSK4=0x20; //Activar rutina interrupcion por input capture
	TIMSK5=0x00; //No necesita rutina de interrupcion

	TCCR4B=0x40; //Hacer que capture sea por flanco de subida de S01 (Bit6=1)
	setBit(TCCR4B,7); //Antirrebotes
	TCCR5B=0x40; //Hacer que capture sea por flanco de subida de S02 (Bit6=1)
	setBit(TCCR5B,7); //Antirrebotes

	sei();
}

int main(){
	
	setup();

	while(1){

	}
	
}

