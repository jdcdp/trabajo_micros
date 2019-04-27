//AUTHOR: Jaime de Castro 14708
//PWM code
#ifndef _PWM_H_
#define _PWM_H_
#include "pwm.c"
#include "pinout.h"


#define PWM_TCCRA TCCR5A
#define PWM_TCCRB TCCR5B
#define PWM_TCCRC TCCR5C
#define PWM_OCR_M1  OCR5A
#define PWM_OCR_M2  OCR5B
#define PWM_OCR_M3  OCR5A
#define PWM_TOP     ICR5
#define PWM_MAX      0xFF

void init_pwm();

        cli();

	DD55=1;	DD54=1;	DD53=1; //output on all pins

	PWM_TOP = PWM_MAX;

	PWM_TCCRA = 0b11111101; //set toggle in all channels

        PWM_TCCRB = 1 << WGM53| 1 << CS51; //set phase-freq correct PWM and preescaler x8

        PWM_OCR_M1 = 0; //set al outputs to 0

	PWM_OCR_M2 = 0;

	PWM_OCR_M3 = 0;

        sei();
}


void pwm(uint8_t motnum, uint8_t speed);{

	switch(motnum){

		case M1 : PWM_OCR_M1=speed;
		case M2 : PWM_OCR_M2=speed;
		case M3 : PWM_OCR_M3=speed;
		case M4 : PWM_OCR_M4=speed;
}


}

#endif
