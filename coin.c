/*
 * coin.c
 *
 * Created: 08/05/2019 20:49:11
 * Author : Guillermo
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "coin.h"
#include "time.h"

uint16_t ta,tb,ta1,tb1,ta2,tb2;
float relacion;

int8_t ultima_moneda;
float saldo;

uint8_t aligned;

void syscall_aligned(){
	
	aligned=1;
	check_saldo();
	
}

void substract_saldo(uint8_t gasto){
	
	saldo-= gasto;
	
}

float get_saldo(){
	return saldo;
}


int get_ultima_moneda(){
	return ultima_moneda;
}

//Funciones Internas---------------------------------------------------

void check_saldo(){
	
	if(saldo > 1.20){
		moveY();
		aligned=0;
	}
	
}

void abrir_barrera(){
	
	//PROBAR MACRO SW9_PIN
	if( (PIND & 0b00000100) != 0){ //Barrera Cerrada es 1
		PORTD &= ~(1<<PD5); //Encender M5
	}
	
}

void cerrar_barrera(){
	
	if( (PIND & 0b00000100) == 0){ //Barrera Abierta es 0 
		PORTD &= ~(1<<PD5); //Encender M5
	}
	
}


uint8_t calculate_ultima_moneda(float relacion){

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
	else{
		return -1; //No reconocida
	}
}

void add_saldo(int ultima_moneda){
	
	if(ultima_moneda!= -1){

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

//Interruptor Barrera (SW9)
ISR(INT2_vect){

	//Frenar Motor
	PORTD |= 1<<PD5;
		
}

//Sensor Optico 1 (SO1)
ISR(S01_TIMERn_CAPT_vect){

	if((S01_PIN) != 0){ //Flanco Subida
		
		//Hacer que capture con flanco de bajada de S01 (Bit6=0)
		S01_TCCRnB&= (~(1<<ICES4));
		
		//Cojo primer punto del tiempo
		ta1=(uint16_t)S01_ICRn;
		tb1=(uint16_t)S01_ICRn;
	
	}

	if((S01_PIN) == 0){ //Flanco Bajada
		
		S01_TCCRnB|= 1<<ICES4; //Hacer que capture con flanco de subida de S01 (Bit6=1)
		
		ta2=(uint16_t)S01_ICRn;
		tb2=(uint16_t)S02_ICRn;

		ta=ta2-ta1;
		tb=tb2-tb1;
		
		relacion=(float)ta/tb;
		ultima_moneda= calculate_ultima_moneda(relacion);
		
		//Mover Barrera
		if(ultima_moneda != -1){
			abrir_barrera();
			esperar_moneda();
		}	
		
		add_saldo(ultima_moneda);
		check_saldo();
		
	}
}


void setup_coin(){

	cli();

	//Monedero-------------------------------------------------
	//Timers para Input Capture
	
	S01_TIMSKn= 1<<ICIE4; //Activar rutina interrupcion por input capture
	S02_TIMSKn=0x00; //No necesita rutina de interrupcion

	S01_TCCRnB= 1<<ICES4; //Hacer que capture sea por flanco de subida de S01 (Bit6=1)
	S01_TCCRnB|= 1<<ICNC4; //Antirruido

	S02_TCCRnB= 1<<ICES1;	//Hacer que capture sea por flanco de subida de S02 (Bit6=1)
	S02_TCCRnB|= 1<<ICNC1;  //Antirruido
	
	//Arrancar Contadores con Preescalado de 8 (Bit1=1)
	S01_TCCRnB|= 1<<CS41;
	S02_TCCRnB|= 1<<CS11;


    //Barrera---------------------------------------------------
	DDRD|= 1<<DDD5; // D5 salida
	DDRD&= (~(1<<DDD2)); //D2 entrada
	PORTD|= 1 << PD5; //Inicializo con freno activado
	
	EICRA= 1 << ISC20; //Interrupcion INT2 se activa por cualquier flanco 
	EIMSK= 1 << INT2;  //Activar INT2

	sei();
	
	esperar_moneda(); //Asegurar posicion inicial barrera: espera y cierra
	
}


int main(void)
{
	setup_coin();

	while (1){
		
	}
}

