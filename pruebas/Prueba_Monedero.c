/*
 * Prueba_Monedero.c
 *
 * Created: 08/05/2019 11:13:50
 * Author : Guillermo
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "Prueba_Monedero.h"

uint16_t ta,tb;
float relacion;

int8_t ultima_moneda;
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
		return -1; //No reconocida
	}
}

void add_saldo(int ultima_moneda){
	
	if(ultima_moneda!=-1){

		if(ultima_moneda==1){
			saldo+=0.10;
		}
		else if(ultima_moneda==2){
			saldo+=0.20;
		}
		else if(ultima_moneda==3){
			saldo+=0.50;
		}
		else if(ultima_moneda==4){
			saldo+=1;
		}

	}
}

//Sensor Optico 1
ISR(S01_TIMERn_CAPT_vect){

	if((S01_PIN) != 0){ //Flanco Subida
		
		//Hacer que capture con flanco de bajada de S01 (Bit6=0)
		S01_TCCRnB&= (~(1<<ICIE4));
		
		//Arrancar Contadores con Preescalado de 8 (Bit1=1)
		S01_TCCRnB|= 1<<CS41;
		S02_TCCRnB|= 1<<CS11;
		
		
	}

	if((S01_PIN) == 0){ //Flanco Bajada

		//Determinacion tipo de moneda y suma del saldo
		ta=(uint16_t)S01_ICRn;
		tb=(uint16_t)S02_ICRn; //Estoy suponiendo que el SO2 siempre se activa antes que se desactiva el S01

		relacion=(float)ta/tb;
		ultima_moneda= calculate_ultima_moneda(relacion);
		add_saldo(ultima_moneda);

		//Parar timers y ...
		S01_TCCRnB|= 1<<ICES4; //Hacer que capture con flanco de subida de S01 (Bit6=1)
		S02_TCCRnB|= 1<<ICES1;//Hacer que capture por flanco de subida de S02 (Bit6=1)

		//Resetear Timers
		S01_TCNTn=0x00;
		S02_TCNTn=0x00;
	}
}

void setup_coin(){
	//Configuracion I/O (Para el setup del main)
	//DDRL&=0b11111100; Bits 0 y 1 entradas

	//Timers para Input Capture
	cli();

	S01_TIMSKn= 1<<ICIE4; //Activar rutina interrupcion por input capture
	S02_TIMSKn=0x00; //No necesita rutina de interrupcion

	S01_TCCRnB= 1<<ICES4; //Hacer que capture sea por flanco de subida de S01 (Bit6=1)
	S01_TCCRnB|= 1<<ICNC4; //Antiruido

	S02_TCCRnB= 1<<ICES1;	//Hacer que capture sea por flanco de subida de S02 (Bit6=1)
	S02_TCCRnB|= 1<<ICNC1;  //Antiruido

	sei();
}

int main(void)
{
	setup_coin();

    /* Replace with your application code */
    while (1) 
    {
    }
}