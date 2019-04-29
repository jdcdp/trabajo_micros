//Pin assignment
#ifndef _PINOUT_H_
#define _PINOUT_H_

//Sensor Optico 1
#define S01PIN	(PINL & 0x01)
#define S01PORT	(PORTL & 0x01)

//Timer con Input Capture
#define S01TCCRnB	TCCR4B
#define S01TCNTn	TCNT4
#define S01TIMSKn 	TIMSK4
#define S01ICRn 	ICR4

//Salto a Rutina
#define S01TIMERn_CAPT_vect TIMER4_CAPT_vect

//Sensor Optico 2
#define S02PIN	(PINL & 0x02)
#define S02PORT	(PORTL & 0x02)

//Timer con Input Capture
#define S02TCCRnB	TCCR5B
#define S02TCNTn 	TCNT5
#define S02TIMSKn 	TIMSK5
#define S02ICRn 	ICR5


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

//drivers/motor.h
#define ENDSTOPS	PORTB

#endif
