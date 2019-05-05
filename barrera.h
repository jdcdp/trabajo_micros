#ifndef _BARRERA_H_
#define _BARRERA_H_


#include <stdint.h>

#define isSet( P, B )  		(P  & (1 << B))           //Consulta el estado del bit B, devuelve un 1 si el bit B es un 1
#define isClr( P, B )  		(~P & (1 << B))           //Consulta el estado del bit B,devuelve un 1 si el bit B es un 0
#define Bk_ON()		        setBit(PORTB,2)           //Activación de la señal M5_bk, frenado dinámico ON
#define Bk_OFF()	        clrBit(PORTB,2)           //Activación de la señal M5_bk, frenado dinámico OFF


//Microinterruptor SW9
#define SW9PIN	(PINB & 0x02)
#define SW9PORT	(PORTB & 0x02)

void abrir_puerta();

void cerrar_puerta();

#endif
