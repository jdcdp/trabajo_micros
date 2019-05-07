//Pin assignment
#ifndef _PINOUT_H_
#define _PINOUT_H_

//Sensor Optico 1
#define S01_PIN		(PINL & 0x01)
#define S01_PORT	(PORTL & 0x01)

//Timer con Input Capture
#define S01_TCCRnB	TCCR4B
#define S01_TCNTn	TCNT4
#define S01_TIMSKn 	TIMSK4
#define S01_ICRn 	ICR4

//Salto a Rutina
#define S01_TIMERn_CAPT_vect TIMER4_CAPT_vect

//Sensor Optico 2
#define S02_PIN		(PINL & 0x02)
#define S02_PORT	(PORTL & 0x02)

//Timer con Input Capture
#define S02_TCCRnB	TCCR1B
#define S02_TCNTn 	TCNT1
#define S02_TIMSKn 	TIMSK1
#define S02_ICRn 	ICR1


//drivers/time_m.h
#define TIME_TCCRA 	TCCR0A
#define TIME_OCR 	OCR0A
#define TIME_TCCRB	TCCR0B

//drivers/pwm.h
#define PWM_TCCRA 	TCCR5A
#define PWM_TCCRB 	TCCR5B
#define PWM_TCCRC 	TCCR5C
#define PWM_OCR_M1  	OCR5A
#define PWM_OCR_M2  	OCR5B
#define PWM_OCR_M3  	OCR5C
#define PWM_TOP     	ICR5
#define PWM_DDR		DDRL

//drivers/motor.h
#define ENDSTOPS	        PINK
#define ENDSTOPDDR	      	DDRK
#define ENSTOP_INTERRUPT  	PCINT1_vect
#define MOTOR_DIR_PORT	  	PORTK
#define M1_DIR		        3
#define M2_DIR            	4
#define M3_DIR            	5




//barrera.h
#define M5_BK
#define SW9


#endif
