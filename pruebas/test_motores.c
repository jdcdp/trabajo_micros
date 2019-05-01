#include <avr/io.h>
#include <avr/interrupt.h>


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
#define PWM_OCR_M3  	OCR1C
#define PWM_TOP     	ICR1
#define PWM_MAX		0xFFFF

//drivers/motor.h
#define ENDSTOPS	PORTB

#define PWM_MAX 255
#define M1 0
#define M2 1
#define M3 2
#define M4 3

void init_pwm(){

	cli();

	DDRB= 1<<DDB7 | 1<<DDB6 | 1<<DDB5; //output on all pins

	PWM_TOP = PWM_MAX;

	PWM_TCCRA = 0b01010100; //set toggle in all channels

	PWM_TCCRB = (1 << WGM13) | (1 << CS11) | (1 << CS10); //set phase-freq correct PWM and preescaler x64

	PWM_OCR_M1 = 0; //set al outputs to 0

	PWM_OCR_M2 = 0;

	PWM_OCR_M3 = 0;

	PWM_TOP=PWM_MAX;

	TIMSK1=0b00001110;

	sei();
}

void pwm(uint8_t motnum, uint8_t speed){

	switch(motnum){

		case M1 : PWM_OCR_M1=speed;
		case M3 : PWM_OCR_M3=speed;
		case M2 : PWM_OCR_M2=speed;
	}
}


int main(void)
{	    init_pwm();
    	//PORTB=1<<7;
		pwm(0,PWM_MAX*0.5); //PIN6
		pwm(1,PWM_MAX); //PIN7
		pwm(2,0); //PIN8
		
		while(1) {}
}

