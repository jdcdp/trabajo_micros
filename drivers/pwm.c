//AUTHOR: Jaime de Castro 14708
//PWM code
#include "pwm.h"

void init_pwm(){

        cli();

	PWM_DDR|= (1<<DDB7) | (1<<DDB6) | (1<<DDB5); //output on all pins

        PWM_TOP = PWM_MAX;

        PWM_TCCRA = (1<<COM1A1) | (1<<COM1A0) | (1<<COM1B1) | (1<<COM1B0) | (1<<COM1C1) | (1<<COM1C0); //set toggle in all channels

        PWM_TCCRB = (1 << WGM13) | (1 << CS11); //set phase-freq correct PWM with ICR as TOP and preescaler x8

        PWM_OCR_M1 = 0; //set al outputs to 0

        PWM_OCR_M2 = 0;

        PWM_OCR_M3 = 0;

        sei();
}

void pwm(uint8_t motnum, uint8_t speed){

        switch(motnum){

                case M1 : PWM_OCR_M1=speed;
                case M2 : PWM_OCR_M2=speed;
                case M3 : PWM_OCR_M3=speed;
	}
}



