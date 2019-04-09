#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#define MAX 300
#define DBOUNCE 10

uint32_t mill =0;

uint8_t v[8]={0};

ISR(TIMER1_COMPA_vect){
	mill++;
	if(mill-v[0]>MAX){
	  PORTC=PORTC>>1;
          for(uint8_t n=0;n<7;n++){
	  	v[i]=v[i+1];
	  }
	  v[7]=0;
	}
	if(mill%DBOUNCE==0) GICR = 1<<INT0;
}


ISR(INT0_vect){
	uint8_t i=0;
	while((v[i])&&(i<7)) i++;
	v[i]=mill;
	PORTC=PORTC<<1;
	GICR=0;
}

int main(){
  cli();
  DDRC=0xFF;
  PORTC=0;
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
  // Enable INT
  GICR = 1<<INT0;
  // Enable trigger on rising edge
  MCUCR =0b00000011;
  sei();


  while(1);
}


