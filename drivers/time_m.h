#ifndef TIME_M_H_
#define TIME_M_H_

//#include "time_m.c"

uint64_t micros_total=0;

//void init_timers();

void micros();

void delay(uint8_t ms);

void setup_timers();

#define TIME_MAX 100 //0.1ms

#define TIME_TCCRnA TCCR0A
#define TIME_OCRnA OCR0A

#define TIME_TCCRnB TCCR0B


#endif