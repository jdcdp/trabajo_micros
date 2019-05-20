/*
 * coin.h
 *
 * Created: 08/05/2019 20:50:22
 *  Author: Guillermo
 */ 


#ifndef COIN_H_
#define COIN_H_


/*Monedero*/

//Rangos Monedas
#define C10MIN	1.16
#define C10MAX	1.20

#define C20MIN	1.32
#define C20MAX 	1.38

#define C50MIN	1.43
#define C50MAX 	1.47

#define E1MIN	1.38
#define E1MAX 	1.42

//Posibles Funciones, seguramente haya que ponerlas en el general
#define setBit(P, B)	(P |= (1 << B))
#define resetBit(P,B) (P &= ( ~(1 << B) ))


//Sensor Optico 1
#define S01_PIN		(PINL & 0x01)

//Timer con Input Capture
#define S01_TCCRnB	TCCR4B
#define S01_TCNTn	TCNT4
#define S01_TIMSKn 	TIMSK4
#define S01_ICRn 	ICR4

//Salto a Rutina
#define S01_TIMERn_CAPT_vect TIMER4_CAPT_vect

//Sensor Optico 2
#define S02_PIN		(PIND & 0x10)

//Timer con Input Capture
#define S02_TCCRnB	TCCR1B
#define S02_TCNTn 	TCNT1
#define S02_TIMSKn 	TIMSK1
#define S02_ICRn ICR1


//Funciones

float get_saldo();
int get_ultima_moneda();

int8_t calculate_ultima_moneda(float relacion);
void add_saldo(int ultima_moneda);


ISR(S01_TIMERn_CAPT_vect);

void setup_coin();



//Funciones

ISR(INT2_vect);

void abrir_barrera();
void cerrar_barrera();


#endif /* COIN_H_ */