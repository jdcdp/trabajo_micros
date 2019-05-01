
#include <avr/io.h>
#include <avr/interrupt.h>
#include "motores.h"

//VARIABLES
unsigned int cnt_SO3;
unsigned int cnt_SO4;
uint8_t parado_M1_M2;
uint8_t cnt_columna;							//en que columna estamos
uint8_t columna;								//a que columna queremos ir
uint8_t fila;									//a que fila queremos ir
uint8_t mov_pos_ini;							//bandera para volver a la posicion incial
uint8_t overflows;
uint8_t estado_int;								//bandera para saber si las interrupciones son por el motor 3 (vale 1) o por los motores 1 o 2 (vale 0)
uint8_t posicionando;
unsigned int aux;
uint8_t engranando;								//bandera para saber cuando estamos bajando el M4 para engranarlo
unsigned int cnt_engrane_SO4;
unsigned int cnt_engrane_SO3;
uint8_t en_posicion;
unsigned int cnt_PWM;
uint8_t encendido;

void setup_variables (){
	
	cnt_SO3 = 0;
	cnt_SO4 = 0;
	parado_M1_M2 = 0;
	cnt_columna = 0;
	columna = 0;
	fila = 0;
	mov_pos_ini = 0;
	engranando = 0;
	cnt_engrane_SO3 = 0;
	cnt_engrane_SO4 = 0;
	posicionando = 0;
	cnt_PWM = 0;
	encendido = 0;

}

//INICIALIZACION
void setup_pines (){
	
	DDRL = DDRL | 0b00111100;						//motores 1 y 2 como salida
	PORTL = PORTL & 0b11000011;						//inicializo motores 1 y 2 apagados

	DDRK = 0b11000000;								//motor 3, sensores opticos SO4 y SO3, sensores fin de carrera motores 1 y 2 (SW1-SW4)
	PORTK = PORTK & 0b00111111;						//inicializo motor 3 apagado

	DDRD = DDRD & 0b11110001;						//sensores fin de carrera del motor 3 (SW5-SW6) y SW7

	//INTERRUPCIONES
	cli();							
	EICRA = EICRA | 0b11111100;						//configuro INT1-INT3 por flanco de subida
	EIMSK = EIMSK | 0b00001110;						//habilito INT1-INT3

	PCMSK2 = 0b00101111;							//habilito PCINT16-PCINT21					SIN SO3
	PCICR = PCICR | 0b00000100;						//habilito grupo 2 (PCINT16-PCINT23)

	//TIMER ANTIRREBOTES
	TCCR3A = 0b00000000;							//modo normal
	TCCR3B = 0b00000001;							//modo normal sin preescalado
	TIMSK3 = 0b00000000;							//interrupciones del timer desactivadas

	//TIMER PWM
	TCCR1A = 0b00000001;							//modo fast PWM 8-bits
	TCCR1B = 0b00001001;							//modo fast PWM 8-bits sin preescalado
	TIMSK1 = 0b00000000;							//interrupciones inicialmente desactivadas
	sei();
}

void setup_motores (){
	setup_variables();
	setup_pines();
}

//FUNCION PARA RESETEAR EL TIMER Y HABILITAR SU INT POR OVERFLOW
void reset_timer3(){
	overflows = OVF_16MS;

	TCNT3H = 0b00000000;
	TCNT3L = 0b00000000;							//resetea la cuenta del timer
	TIMSK3 = 0b00000001;							//habilita int por overflow
}

void reset_timer1(){
	cnt_PWM = 0;
	encendido = 1;
	
	TCNT1H = 0b00000000;
	TCNT1L = 0b00000000;							//resetea la cuenta del timer
	TIMSK1 = 0b00000001;							//habilita la int por overflow
}

//FUNCIONES PARA PWM DEL MOTOR 3
void M3_off_PWM(){
	M3_off();
	TIMSK1 = 0b00000000;							//deshabilitamos la int por overflow del timer del PWM
}

void M3_derecha_PWM(){
	M3_derecha();
	reset_timer1();
}

void M3_izquierda_PWM(){
	M3_izquierda();
	reset_timer1();
}

//INTERRUPCIONES
ISR ( INT1_vect ){									//interrupcion por SW5 (cuando M3 llegue a la derecha)
	reset_timer3();
	EIMSK = EIMSK & 0b11111101;						//deshabilito INT1
	estado_int = 1;
}

ISR ( INT2_vect ){									//interrupcion por SW6 (cuando M3 llegue a la izquierda)
	reset_timer3();
	EIMSK = EIMSK & 0b11111011;						//deshabilito INT2
	estado_int = 1;
}

ISR ( INT3_vect ){									//interrupcion por SW7 (cuando pase por una posicion de engrane)
	reset_timer3();
	EIMSK = EIMSK & 0b11110111;						//deshabilito INT3
	estado_int = 1;
}

ISR ( PCINT2_vect ){								//interrupcion por SW1, SW2, SW3, SW4, SO3, SO4
	reset_timer3();
	PCICR = PCICR & 0b11111011;						//deshabilitamos PCINT grupo 2 (16-23)
	estado_int = 0;
}

ISR (TIMER3_OVF_vect){

	if ( overflows-- == 0 ){
		if ( estado_int == 1 ){	
			if ( (PIND & 0b00000010) == 0b00000010 ){		//INT por SW5 (motor 3 derecha) 
				M3_off_PWM();
				if (mov_pos_ini == 1){
					M1_abajo();
					M2_abajo();
					mov_pos_ini = 0;
				}
				cnt_columna = 0;
			}
			if ( (PIND & 0b00000100) == 0b00000100 ){		//INT por SW6 (motor 3 izquierda)
				M3_off_PWM();
			}
			if ( (PIND & 0b00001000) == 0b00000000 ){		//INT por SW7
				cnt_columna ++;
				if (cnt_columna == columna){
					M3_off_PWM();
					M2_abajo();								//cuando estemos en la columna que queremos, bajamos motores 1 y 2 hasta que engranen
					M1_abajo();
					engranando = 1;
				}
			}
			EIMSK = EIMSK | 0b00001110;						//habilitamos INT1-3
			TIMSK3 = 0b00000000;							//deshabilitamos interrupcion por overflow
			EIFR = 0b00001110;								//borramos banderas SW5-SW6-SW7
		}
		else if ( estado_int == 0 ){
			
			/*if ( PINK & 0b00010000 )						//SO3
				cnt_SO3++;*/

			if ( engranando == 1 ){
				if ( PINK & 0b00100000 )					//SO4 para engranar
					cnt_engrane_SO4++;
				if ( fila == 1 ){
					if ( cnt_engrane_SO4 == POS_ENGRANE_1 ){
						M1_off();
						M2_off();
						en_posicion = 1;					//se pone a 1 para saber que estamos en posicion, listos para dispensar
						engranando = 0;
						posicionando = 0;
						cnt_SO3 = 0;
						cnt_SO4 = 0;
						cnt_engrane_SO4 = 0;
					}
				}
				if ( fila == 2 ){
					if ( cnt_engrane_SO4 == POS_ENGRANE_2 ){
						M1_off();
						M2_off();
						en_posicion = 1;					//se pone a 1 para saber que estamos en posicion, listos para dispensar
						engranando = 0;
						posicionando = 0;
						cnt_SO3 = 0;
						cnt_SO4 = 0;
						cnt_engrane_SO4 = 0;
					}
				}
				if ( fila == 3 ){
					if ( cnt_engrane_SO4 == POS_ENGRANE_3 ){
						M1_off();
						M2_off();
						en_posicion = 1;					//se pone a 1 para saber que estamos en posicion, listos para dispensar
						engranando = 0;
						posicionando = 0;
						cnt_SO3 = 0;
						cnt_SO4 = 0;
						cnt_engrane_SO4 = 0;
					}
				}
				if ( fila == 0 ){
					if ( cnt_engrane_SO4 == POS_ENGRANE_0 ){
						M1_off();
						M2_off();
						M3_derecha();
						engranando = 0;
						cnt_SO3 = 0;
						cnt_SO4 = 0;
						cnt_engrane_SO4 = 0;
					}
				}
			}
			else {
				if ( PINK & 0b00100000 )					//SO4 para posicionar en fila correspondiente
					cnt_SO4++;

				if ( fila == 1 && (cnt_SO4 == ALTURA1) ){
					M1_off();
					M2_off();
					parado_M1_M2 = 1;
				}

				if ( fila == 2 && (cnt_SO4 == ALTURA2) ){
					M1_off();
					M2_off();
					parado_M1_M2 = 1;
				}

				if ( fila == 3 && ((PINK & 0b00000101) == 0b00000101) ){
					M1_off();
					M2_off();
					parado_M1_M2 = 1;
				}

				if ( parado_M1_M2 == 1 ){
					M3_izquierda_PWM();
					parado_M1_M2 = 0;
				}
			}
			
			if(posicionando == 0){
				aux = PINK & 0b00001111;
				switch (aux){
					case 0b00000101:							//SW1 y SW3 (motores 1 y 2 arriba)
					M1_off();
					M2_off();
					cnt_SO3 = 0;
					cnt_SO4 = 0;
					break;
					case 0b00001010:							//SW2 y SW4 (motores 1 y 2 abajo)
					M2_off();
					M1_off();
					cnt_SO3 = 0;
					cnt_SO4 = 0;
					en_posicion = 1;							//se pone a 1 para saber que estamos en la posicion inicial
					break;
					default:
					break;
				}
			}
			PCICR = PCICR | 0b00000100;							//habilitamos PCINT grupo 2 (16-23)
			PCIFR = 0b00000100;									//borramos la bandera de PCINT grupo 2 (16-23)
			TIMSK3 = 0b00000000;								//deshabilitamos interrupcion por overflow
		}	
	}
}

ISR(TIMER1_OVF_vect){
	
	cnt_PWM++;

	if ( cnt_PWM == OVF_ON_PWM && encendido == 1 ){
		PORTK = PORTK & 0b10111111;								//apagamos M3 manteniendo la direccion
		encendido  = 0;
		cnt_PWM = 0;
	}
	if ( cnt_PWM == OVF_OFF_PWM && encendido == 0 ){
		PORTK = PORTK | 0b01000000;								//volvemos a encender M3
		encendido = 1;
		cnt_PWM = 0;
	}
}

//FUNCIONES PARA MOVER LOS MOTORES
void pos_inicial(){
	fila = 0;
	columna = 0;
	mov_pos_ini = 1;
	posicionando = 0;
	engranando = 1;
}

void mover (unsigned int posicion){

	en_posicion = 0;											//la reseteamos a 0 para saber que nos estamos moviendo							

	switch (posicion){											//DECODIFICADOR PARA EL TECLADO
		case 0:	
			if (PIND & 0b00000010){								//si M3 esta ya en la derecha, ir directamente hacia abajo
				posicionando = 0;
				M1_abajo();
				M2_abajo();
			}
			else {
				pos_inicial();
				M1_arriba();
				M2_arriba();
			}
			break;
		case 1:		fila = 3;	columna = 3;	mov_pos_ini = 0;	posicionando = 1;	M1_arriba();	M2_arriba();	break;
		case 2:		fila = 3;	columna = 2;	mov_pos_ini = 0;	posicionando = 1;	M1_arriba();	M2_arriba();	break;
		case 3:		fila = 3;	columna = 1;	mov_pos_ini = 0;	posicionando = 1;	M1_arriba();	M2_arriba();	break;
		case 4:		fila = 2;	columna = 3;	mov_pos_ini = 0;	posicionando = 1;	M1_arriba();	M2_arriba();	break;
		case 5:		fila = 2;	columna = 2;	mov_pos_ini = 0;	posicionando = 1;	M1_arriba();	M2_arriba();	break;
		case 6:		fila = 2;	columna = 1;	mov_pos_ini = 0;	posicionando = 1;	M1_arriba();	M2_arriba();	break;
		case 7:		fila = 1;	columna = 3;	mov_pos_ini = 0;	posicionando = 1;	M1_arriba();	M2_arriba();	break;
		case 8:		fila = 1;	columna = 2;	mov_pos_ini = 0;	posicionando = 1;	M1_arriba();	M2_arriba();	break;
		case 9:		fila = 1;	columna = 1;	mov_pos_ini = 0;	posicionando = 1;	M1_arriba();	M2_arriba();	break;
		default:	M1_off();	M2_off();		M3_off_PWM();				break;
	}
}