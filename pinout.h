//Pin assignment
#ifndef _PINOUT_H_
#define _PINOUT_H_

//Sensor Optico 1
#define S01_PIN	(PINL & 0x01)
#define S01_PORT	(PORTL & 0x01)

//Timer con Input Capture
#define S01_TCCRnB	TCCR4B
#define S01_TCNTn	TCNT4
#define S01_TIMSKn 	TIMSK4
#define S01_ICRn 	ICR4

//Salto a Rutina
#define S01_TIMERn_CAPT_vect TIMER4_CAPT_vect

//Sensor Optico 2
#define S02_PIN	(PINL & 0x02)
#define S02_PORT	(PORTL & 0x02)

//Timer con Input Capture
#define S02_TCCRnB	TCCR5B
#define S02_TCNTn 	TCNT5
#define S02_TIMSKn 	TIMSK5
#define S02_ICRn 	ICR5


//drivers/time_m.h
#define TIME_TCCRA 	TCCR0A
#define TIME_OCR 	OCR0A
#define TIME_TCCRB	TCCR0B

//drivers/pwm.h
#define PWM_TCCRA 	TCCR1A
#define PWM_TCCRB 	TCCR1B
#define PWM_TCCRC 	TCCR1C
#define PWM_OCR_M1  	OCR1A
#define PWM_OCR_M2  	OCR1B
#define PWM_OCR_M3  	OCR1A
#define PWM_TOP     	ICR1
#define PWM_DDR		DDRB

//drivers/motor.h
#define ENDSTOPS	        PINK
#define ENDSTOPDDR	      DDRK  	
#define ENSTOP_INTERRUPT  PCINT1_vect
#define MOTOR_DIR_PORT	  PORTK
#define M1_DIR		        2
#define M2_DIR            6
#define M3_DIR            7




//barrera.h
#define M5_BK
#define SW9


#endif
