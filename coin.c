#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "coin.h"
#include "pinout.h"

uint16_t ta,tb;
float relacion;

uint8_t ultima_moneda;
float saldo;


float get_saldo(){
	return saldo;
}

int get_ultima_moneda(){
	return ultima_moneda;
}

//Funciones Internas

int calculate_ultima_moneda(float relacion){
	
	if((relacion > C10MIN) && (relacion < C10MAX)){
		return 1; //10 cent
	}
	else if((relacion > C20MIN) && (relacion < C20MAX)){
		return 2; //20 cent
	}
	else if((relacion > C50MIN) && (relacion < C50MAX)){
		return 3; //50 cent
	}
	else if((relacion > E1MIN) && (relacion < E1MAX)){
		return 4; //1 euro
	}
	else {
		return 0; //No reconocida
	}
}

void add_saldo(int ultima_moneda){
	
	if(ultima_moneda==1){
		saldo+=0.10;
	}
	else if((ultima_moneda==2){
		saldo+=0.20;
	}
	else if((ultima_moneda==3){
		saldo+=0.50;
	}
	else if(ultima_moneda==4){
		saldo+=1;
	}
}

//Sensor Optico 1
ISR(S01TIMERn_CAPT_vect){
	
	if((S01PIN) != 0){ //Flanco Subida
	
		//Arrancar Contadores con Preescalado de 8 (Bit1=1) y...
		S01TCCRnB=0x02; //Hacer que capture con flanco de bajada de S01 (Bit6=0)
		S02TCCRnB=0x42; //Flanco subida de S02 (Bit6=1)	
	}
	
	if((S01PIN) == 0){ //Flanco Bajada
		
		//Determinacion tipo de moneda y suma del saldo
		ta=(uint16_t)S01ICRn;
		tb=(uint16_t)S02ICRn; //Estoy suponiendo que el SO2 siempre se activa antes que se desactiva el S01
		
		relacion=(float)ta/tb;
		ultima_moneda= calculate_ultima_moneda(relacion);
		add_saldo(ultima_moneda);

		//Parar timers y ...
		S01TCCRnB=0x40; //Hacer que capture con flanco de subida de S01 (Bit6=1)
		S02TCCRnB=0x40; //Hacer que capture por flanco de subida de S02 (Bit6=1)
		
		//Resetear Timers
		S01TCNTn=0x00;
		S02TCNTn=0x00;
	}
}

void setup_coin(){
	//Configuracion I/O (Para el setup del main)
	//DDRL&=0b11111100; Bits 0 y 1 entradas
	
	//Timers para Input Capture
	cli();
	
	S01TIMSKn=0x20; //Activar rutina interrupcion por input capture
	S02TIMSKn=0x00; //No necesita rutina de interrupcion

	S01TCCRnB=0x40; //Hacer que capture sea por flanco de subida de S01 (Bit6=1)
	setBit(S01TCCRnB,7); //Antirrebotes
	
	S02TCCRnB=0x40; //Hacer que capture sea por flanco de subida de S02 (Bit6=1)
	setBit(S02TCCRnB,7); //Antirrebotes

	sei();
}
