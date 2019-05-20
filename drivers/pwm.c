//AUTHOR: Jaime de Castro 14708
//PWM code
#include "pwm.h"

void pwm_init(){

        cli();

	PWM_DDR|= (1<<DDB3) | (1<<DDB4) | (1<<DDB5); //output on all pins

	PWM_TOP = PWM_MAX;

	PWM_OCR_M1 = PWM_MAX; //set al outputs to 0

	PWM_OCR_M2 = PWM_MAX;

	PWM_OCR_M3 = PWM_MAX;

	PWM_TCCRA = (1<<COM1A1) | (1<<COM1A0) | (1<<COM1B1) | (1<<COM1B0) | (1<<COM1C1) | (1<<COM1C0); //set toggle in all channels

	PWM_TCCRB = (1 << WGM13) | (1 << CS11); //set phase-freq correct PWM with ICR as TOP and prescaler x8

        sei();
}

void pwm(uint8_t motnum, uint16_t speed){

        switch(motnum){

                case M1 : PWM_OCR_M1=PWM_MAX-speed; break;
                case M2 : PWM_OCR_M2=PWM_MAX-speed; break;
                case M3 : PWM_OCR_M3=PWM_MAX-speed; break;
	}
}



