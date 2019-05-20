
#include <avr/interrupt.h>
#include <avr/io.h>

int debugM1,debugM2;

ISR(INT0_vect){
	debugM1++;
}
ISR(INT1_vect){
	debugM2++;
}

int main(void)
{	
	  cli();
	  EICRA|=(1<<ISC10 | 1<<ISC11 | 1<<ISC00 | 1<<ISC01); //11=rising
	  EIMSK|=(1<<INT1 | 1<<INT0);
	  DDRD=0;
	  sei();
	  
    /* Replace with your application code */
    while (1) {}
    
}
