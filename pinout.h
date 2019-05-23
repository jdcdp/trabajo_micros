//Pin assignment
#ifndef _PINOUT_H_
#define _PINOUT_H_

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
#define S02_ICRn 	ICR1

/*Barrera*/

//M5
#define M5_BK_PIN	(PIND & 0x10)

//SW9
#define SW9_PIN		(PIND & 0x04)



//drivers/time_m.h
#define TIME_TCCRA 	TCCR0A
#define TIME_OCRA 	OCR0A
#define TIME_TCCRB	TCCR0B
#define TIME_TIMSK	TIMSK0

//----------------------------
//	Barrera

#define BARRERA_TCCRB	TCCR3B
#define BARRERA_OCRA	OCR3A
#define BARRERA_CNT	TCNT3
#define BARRERA_TIMSK	TIMSK3
//-----------------------------


//drivers/pwm.h
#define PWM_TCCRA	TCCR5A
#define PWM_TCCRB	TCCR5B
#define PWM_TCCRC	TCCR5C
#define PWM_OCR_M1  	OCR5A
#define PWM_OCR_M2  	OCR5B
#define PWM_OCR_M3  	OCR5C
#define PWM_TOP     	ICR5
#define PWM_DDR		DDRL

//drivers/motor.h
#define ENDSTOPS	        PINK
#define ENDSTOPDDR	      	DDRK
#define DIRDDR			DDRL
#define PIN_SW7			(PINK & 0b0100000)
#define OPTENDDDR		DDRD
#define ENDSTOP_INTERRUPT  	PCINT2_vect
#define MOTOR_DIR_PORT	  	PORTL
#define M1_DIR          	2
#define M2_DIR            	6
#define M3_DIR            	7
#define SO3			INT0_vect
#define SO4			INT1_vect
#define SW1			0
#define SW2                     1
#define SW3                     2
#define SW4                     3
#define SW5                     4
#define SW6                     5
#define SW7                     6
#define SW8                     7


//teclado.h
#define KEYPAD (PCINT0_vect)

#endif
