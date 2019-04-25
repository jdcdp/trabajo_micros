#include "time_m.h"


void init_timers(){
	//TO DO
	//Inicializar timer para delays de duracion F_CPU/1000000L
}

void micros(){
	//TO DO
	//Interrupcion que sume 1 a micros_total

}

void delays(uint8_t ms){
	sei();
	int end_time=micros()+ms*1000;
	while (read_time_ms()<end_time)//change with an interruption and HOLD()
}
