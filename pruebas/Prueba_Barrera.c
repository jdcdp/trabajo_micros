/*
 * Prueba_Barrera.c
 *
 * Created: 07/05/2019 12:14:08
 * Author : Guillermo
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "Prueba_Barrera.h"

// PROBAR PRIMERO EN MAIN POR SEPARADO

void abrir_barrera(){
	
	if( SW9_PIN == 0){ //Barrera Cerrada es 0 COMPROBAR
		PORTD &= ~(1<<PD5); //Encender M5
	}
	
}

void cerrar_barrera(){
	
	if( SW9_PIN != 0){ //Barrera Abierta es 1 COMPROBAR
		PORTD &= ~(1<<PD5); //Encender M5
	}
	
}	


	
//Funciones Internas-------------------------------------------------------------------

//SW9
ISR(INT2_vect){ 

	//Frenar Motor
		//Debe estar M5_bk a 1 y activado el en del M5 en la maqueta
	PORTD |= PD5;
	
}


void setup_barrera(){
	
	cli();
	
	DDRD|= 1<<DDD5; // D5 salida
	DDRD&= (~(1<<DDD2)); //D2 entrada
	PORTD|=1 << PD5; //Inicializo con freno activado
	
	//FALTA COMPROBAR POSIBLE CONTROL DE DIRECCION-----------
	//Ver si activa SW9 bien
	
	EIMSK= 1 << INT2;  //Activar INT2
	EICRA= 1 << ISC20; //Interrupcion INT2 se activa por cualquier flanco

	sei();
}



int main(void)
{
	setup_barrera();
	cerrar_barrera();
	
	//abrir_barrera();
	
    while (1) 
    {
		
    }
}

