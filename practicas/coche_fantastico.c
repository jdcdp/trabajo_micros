#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define MS 100

uint8_t dir_f=0;

ISR(TIMER1_COMPA_vect){

  if (c++ == MS){
	c=0;
	if(dir_f) PORTC=PORTC>>1;
	else      PORTC=PORTC<<1;
	if(PORTC==0x80) dir_f=1;
	else if(PORTC==0x01) dir_f=0;
	}
}



int main(){
  cli();
  DDRC=0xFF;
  PORTC=1;

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

// 1000 Hz (8000000/((124+1)*64))
  OCR1A = 124;
  // CTC
  TCCR1B |= (1 << WGM12);
  // Prescaler 64
  TCCR1B |= (1 << CS11) | (1 << CS10);
  // Output Compare Match A Interrupt Enable
  TIMSK1 |= (1 << OCIE1A);
  sei();


  while(1);
}


